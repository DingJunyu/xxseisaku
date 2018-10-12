#include"game.h"
//ヘッドファイルなどと構造体の宣言はgame.hにある
//attack.cは攻撃関連関数
//round.cは毎ターン行動関数
//shortones.cは短い関数
//healは治療バッフ関数
//showmapはすべての輸出関連
//moeveは移動関連
//randomdataはユニットデータを生成用関数

int main()
{
	int i,j=1;//テスト用変数
	int tarx[5] = {0};//a[][1]--->x座標a[][2]---->y座標
	int tary[5] = { 0 };
	int tarc = 0;//選べるターゲットの数
	int inpu1,inpu2=0;
	int resal=4, resen=4;//味方残り人数　敵残り人数
	int coun=1;
	char dataname[100];

	FILE *up;

	struct unitdata allies[10]; //ホルダー 1 2 3 4 対応
	struct unitdata enemy[10]; //ホルダー 5 6 7 8対応

	int map[8+1][10+1][4];//[0]は地形を保存   [1]はホルダー   [2]はai側ルート探す用   [3]は輸出用(選択)(1-左 2-上 3-右 4-下 5-輸出しない)

	title();
	
	while (1)
	{
		for (i = 1; i <= 4; i++)//ユニットのデータ初期化
		{
			resetunit(&allies[i]);
			resetunit(&enemy[i]);
		}

		while (1)//タイトルとマップ選択
		{
			printf("   ・マップの番号を選んでください(1~6):");
			scanfwild(&inpu1, 1, 6);
			reset(map); //マップを全部クリア
			readmap(map, inpu1);
			sprintf_s(dataname, 100, ".//mapdata//unitpos%d.txt", inpu1);
			fopen_s(&up, dataname, "r");
			for (i = 1; i <= 4; i++)
			{
				fscanf_s(up, "%d %d", &allies[i].px, &allies[i].py);
				fscanf_s(up, "%d", &map[allies[i].py][allies[i].px][1]);
			}
			for (i = 1; i <= 4; i++)
			{
				fscanf_s(up, "%d %d", &enemy[i].px, &enemy[i].py);
				fscanf_s(up, "%d", &map[enemy[i].py][enemy[i].px][1]);
			}
			fclose(up);
			show(map, &allies[1], &enemy[1]);
			printf("--------------------マップ%2d--------------------\n",inpu1);
			printf("このマップで決めるか?YES--->1NO--->1以外:");
			scanf_s("%d", &inpu1);
			if (inpu1 == 1)
				break;
		}
		//残る人数をリセット
		resal = 4; resen = 4;

		//チームAとBのユニットタイプを選ぶ
		for (i = 1; i <= 4; i++)
		{
			show(map, &allies[1], &enemy[1]);
			randomdata(&allies[i], i,1);
			show(map, &allies[1], &enemy[1]);
			randomdata(&enemy[i], i, 2);
		}

		
		while (resal > 0 && resen > 0)
		{
			printf("-----------------------ラウンド %d-----------------------", coun);
			getchar();
			i = 1;
			//チームabのコメントは同じ
			while (i <= 4)
			{
				if (round(&i, &allies[1], &enemy[1], map, &resen) == 1)
					break;
				if (round(&i, &enemy[1], &allies[1], map, &resal) == 1)
					break;
				i++;
			}
			coun++;
		}

		show(map, &allies[1], &enemy[1]);
		if (resen == 0)
			printf("プレーヤー１の勝つだ\n");
		if (resal == 0)
			printf("プレーヤー２の勝つだ\n");
		printf("続けるか？0->YES");
		scanf_s("%d", &inpu1);
		if (inpu1 != 0)
			break;
	}
	return 0;
}