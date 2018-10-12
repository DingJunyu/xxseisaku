#include"game.h"

/*round関数*/
/*r:該当ユニットの番号,x:x座標,y:y座標,res:残ったユニット数*/
/*return値: 2:該当ターゲットはもう死んだ 1:チームはもう全滅 0:なんでもない*/
int round(int *r,void *x,void *y,int *res)
{
	/*ターゲットデータ保存用変数tarx,tary,tarc*/
	int tary[5];
	int tarx[5];
	int tarc=0;
	/*移動回数統計変数movecount*/
	int movecount;
	/*入力用変数inpu1,inpu2*/
	int inpu1=0,inpu2=0;
	/*繰り返す用変数j,k*/
	int j, k;
	/*ターゲット番号修正用変数ba,sa*/
	/*マップの座標によって、各チームのユニット番号に変わる*/
	int ba, sa;
	/*行動順位修正用変数*/
	int mark = 0;
	int canyoumove;

	struct unitdata *a, *b;

	a = (struct unitdata*)x;
	b = (struct unitdata*)y;

	if (*res <= 0)
		return 1;

	/*Aチームのターン*/
	/*rの値を次のBチームのユニットになる*/
	if (*r <= 4)
	{
		j = *r-1;
		*r += 4;
		mark = 1;
	}
	/*Bチームのタータン*/
	/*ｒの値はAチームの範囲内に戻る*/
	if (*r > 4 && mark == 0)
	{
		j = *r - 5;
		*r -= 4;
	}

	/*ターゲットは死んだ場合はターンをスキップ*/
	if ((a+j)->hp <= 0)
		return 2;

	/*画面を描く*/
	kansushow(a,b,*r);
	roundshow(*r, j);
	/*行動番号を入力*/
	printf("行動を選んでください(1.移動 2.攻撃 3.回復/スキール 4.防御態勢 0,終わる)：");
	scanfwild(&inpu1, 0, 4);

	movecount = 0;
	/*移動*/
	while (inpu1 == 1)
	{
		++movecount;
		canyoumove=showmove(a+j);
		kansushow(a,b,*r);
		roundshow(*r, j);
		movem(a+j, canyoumove);
		kansushow(a,b,*r);
		roundshow(*r, j);
		/*もう続けて移動ができない場合*/
		if ((a+j)->move == 1 || movecount == (a+j)->move || map[(a+j)->py][(a+j)->px][0] == 6||canyoumove==0)
		{
			printf("行動を選んでください(1.攻撃 2.回復/スキール 3.防御態勢 0,終わる)：");
			scanfwild(&inpu2, 0, 3);
			inpu1 = 0;
			break;
		}
		/*まだ続ける場合*/
		else
		{
			printf("行動を選んでください(1.移動 2.攻撃 3.回復/スキール 4.防御態勢 0,終わる)：");
			scanfwild(&inpu1, 0, 4);
			if (inpu1 != 1)
				break;
		}
	}
	
	/*攻撃*/
	if (inpu1 == 2 || inpu2 == 1)
	{
		attshow(a+j,  &tarx[1], &tary[1], &tarc);
		kansushow(a,b,*r);
		if (tarc != 0)
		{			
			roundshow(*r, j);	
			for (k = 1; k <= tarc; ++k)
			{
				if (map[tary[k]][tarx[k]][1] > 4)
					sa = map[tary[k]][tarx[k]][1] - 5;
				else
					sa = map[tary[k]][tarx[k]][1]-1;
				printf("%d番:X:%d Y:%d %s %d/%d\n", k, tarx[k], tary[k], (b + sa)->name, (b + sa)->hp, (b + sa)->maxhp);
			}
			*res -= attack(a+j, b, &tarx[1], &tary[1], tarc);
			if (*res <= 0)//敵が全部死んだらおわり
				return 1;
		}
		if (tarc <= 0)
		{
			printf("攻撃できるターゲットがいません。\n");
			printf("2.回復/スキール 3.防御態勢 0,終わる。\n");
			scanf_s("%d", &inpu2);
		}
		/*ターゲットをリセット*/
		tarc = 0; tarx[1] = 0; tary[1] = 0;
	}

	/*治療*/
	if (inpu1 == 3 || inpu2 == 2)
	{
		healshow(a+j, &tarx[1], &tary[1], &tarc);
		kansushow(a,b,*r);
		if (tarc != 0)
		{
			roundshow(*r, j);
			printf("1番:X:%d Y:%d %s %d/%d\n", tarx[1], tary[1], (a + j)->name, (a + j)->hp, (a + j)->maxhp);
			for (k = 2; k <= tarc; ++k)
			{
				if (map[tary[k]][tarx[k]][1] > 4)
					ba = map[tary[k]][tarx[k]][1] - 4;
				else
					ba = map[tary[k]][tarx[k]][1] - 1;
				printf("%d番:X:%d Y:%d %s %d/%d\n", k, tarx[k], tary[k], (a + ba)->name, (a + ba)->hp, (a + ba)->maxhp);
			}
			heal(a+j, a, &tarx[1], &tary[1], tarc);
		}
		/*ターゲットをリセット*/
		tarc = 0; tarx[1] = 0; tary[1] = 0;
	}

	(a+j)->skill = 0;

	/*バッフ*/
	if (inpu1 == 4 || inpu2 == 3)
	{
		defendmode(&(a+j)->skill);
		printf("%sは防御態勢に移行された\n", (a+j)->name);
	}

	printf("ターン終了");
	rewind(stdin);
	getchar();

	return 0;
}