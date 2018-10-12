#include"game.h"

int main()
{
	/*テスト、繰り返す用変数i,j*/
	int i,j=1;
	/*入力用変数inpu1,inpu2*/
	int inpu1,inpu2=0;
	/*チームA残り人数resal,チームB残り人数resen*/
	int resal=4, resen=4;
	/*ラウンドカウンター*/
	int coun=1;

	/*構造体を使ってチームAとチームBを宣言*/
	/*ホルダー対応：*/
	/*allies 1~4: ホルダー 1~4*/
	/*enemy 1~4:ホルダー 5~8*/
	struct unitdata allies[10];
	struct unitdata enemy[10];


	while (1)
	{
		/*全ユニットを初期化*/
		for (i = 1; i <= 4; i++)
		{
			resetunit(&allies[i]);
			resetunit(&enemy[i]);
		}

		/*マインメニューを描く*/
		title();
		printf("  ・1.ランダムマップ\n  ・2.キャーペンマップ\n  ・3.終わる\n  ");
		scanfwild(&inpu1, 1, 3);

		if (inpu1 == 3)
			break;

		/*ランダムマップを生成、決定*/
		while (inpu1 == 1)
		{
			printf("                                                                loading...");
			randommap();
			findtheposition(&allies[1], &enemy[1]);
			show(&allies[1], &enemy[1]);

			printf("このマップで決めますか?YES--->1NO--->1以外");
			scanf_s("%d", &inpu2);
			if (inpu2 == 1)
				break;
		}

		if (inpu1 == 2)
		choosemap(&allies[1], &enemy[1]);

		printf("  ・1.対戦モード\n  ・2.パソコンとの対戦\n");
		scanfwild(&inpu1, 1, 2);
		/*両チーム残る人数をリセット*/
		resal = 4; resen = 4;

		/*ユニットを選ぶ*/
		for (i = 1; i <= 4; i++)
		{
			show(&allies[1], &enemy[1]);
			randomdata(&allies[i], i,1, 1);
			if(inpu1==1)
			show(&allies[1], &enemy[1]);
			randomdata(&enemy[i], i, 2, inpu1);
		}

		
		/*PVPラウンド部分*/
		while (resal > 0 && resen > 0 && inpu1 == 1)
		{
			printf("-----------------------ラウンド %d-----------------------", coun);
			getchar();
			i = 1;
			while (i <= 4)
			{
				if (round(&i, &allies[1], &enemy[1], &resen) == 1)
					break;
				if (round(&i, &enemy[1], &allies[1], &resal) == 1)
					break;
				i++;
			}
			coun++;
		}

		/*PVEラウンド部分*/
		while (resal > 0 && resen > 0 && inpu1 == 2)
		{
			printf("-----------------------ラウンド %d-----------------------", coun);
			getchar();
			i = 1;
			while (i <= 4)
			{
				if (round(&i, &allies[1], &enemy[1], &resen) == 1)
					break;
				if (myturn(&i, &enemy[1], &allies[1], &resal) == 1)
					break;
				i++;
			}
			coun++;
		}

		/*最後のマップ状態を表す*/
		show(&allies[1], &enemy[1]);
		if (resen == 0)
			printf("プレーヤー１の勝つだ\n");
		if (resal == 0)
			printf("プレーヤー２の勝つだ\n");

		system("pause");
	}
	return 0;
}
//1631 2018.07.09