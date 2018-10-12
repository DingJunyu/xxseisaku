#include"game.h"
void defendup(int *dp, int *dm, int *miss, int x, int y, int status);
void attup(int *att, int status);
void hithim(int attype, int att, int dp, int dm, int *hp);
int tf(int x);
//攻撃部分
void attshow(void *x,int *tx,int *ty,int *tc)
{
	//命中判定------>4d3 6+sa以下--->ミス 6+sa以上=----->あたる sa----->地形の差----->原と部屋は2/-2 川を越えるは1
	struct unitdata *a;//aとxは攻撃する側、bとyは攻撃される側

	a = (struct unitdata*)x;

		if (a->atttype == 3 || a->atttype == 4|| a->atttype == 2 || a->atttype == 5)
		{
			if(checkfield(a->px - 1,a->py-1)==1)
			if (teamcheck(map[a->py][a->px][1],map[a->py-1][a->px-1][1])==1) //左上
			{
				*tx = a->px - 1; *ty = a->py - 1;
				*tx++; *ty++; *tc += 1;
			}
			if (checkfield(a->px + 1, a->py - 1) == 1)
			if (teamcheck(map[a->py][a->px][1],map[a->py - 1][a->px + 1][1])==1) //右上
			{
				*tx = a->px + 1; *ty = a->py - 1;
				*tx++; *ty++; *tc += 1;
			}
			if (checkfield(a->px - 1, a->py + 1) == 1)
			if (teamcheck(map[a->py][a->px][1],map[a->py + 1][a->px - 1][1])==1) //左下
			{
				*tx = a->px - 1; *ty = a->py + 1;
				*tx++; *ty++; *tc += 1;
			}
			if (checkfield(a->px + 1, a->py + 1) == 1)
			if (teamcheck(map[a->py][a->px][1], map[a->py + 1][a->px + 1][1]) == 1) //左下
			{
				*tx = a->px + 1; *ty = a->py + 1;
				*tx++; *ty++; *tc += 1;
			}
		}

		if (checkfield(a->px + 1, a->py) == 1)
			if (teamcheck(map[a->py][a->px][1], map[a->py][a->px + 1][1]) == 1) //右
			{
				*tx = a->px + 1; *ty = a->py;
				*tx++; *ty++; *tc += 1;
			}
		if (checkfield(a->px - 1, a->py) == 1)
			if (teamcheck(map[a->py][a->px][1], map[a->py][a->px - 1][1]) == 1) //左
			{
				*tx = a->px - 1; *ty = a->py;
				*tx++; *ty++; *tc += 1;
			}
		if (checkfield(a->px, a->py - 1) == 1)
			if (teamcheck(map[a->py][a->px][1], map[a->py - 1][a->px][1]) == 1) //上
			{
				*tx = a->px; *ty = a->py - 1;
				*tx++; *ty++; *tc += 1;
			}
		if (checkfield(a->px, a->py + 1) == 1)
			if (teamcheck(map[a->py][a->px][1], map[a->py + 1][a->px][1]) == 1) //下
			{
				*tx = a->px; *ty = a->py + 1;
				*tx++; *ty++; *tc += 1;
			}

		if (a->atttype == 2||a->atttype==5)
		{
			if (checkfield(a->px+2, a->py) == 1)
			if(map[a->py][a->px +1][0]!=1)
			if (teamcheck(map[a->py][a->px][1], map[a->py][a->px + 2][1]) == 1) //右2
			{
				*tx = a->px + 2; *ty = a->py;
				*tx++; *ty++; *tc += 1;
			}
			if (checkfield( a->px-2,a->py) == 1)
			if(map[a->py][a->px - 1][0]!=1)
			if (teamcheck(map[a->py][a->px][1], map[a->py][a->px - 2][1]) == 1)  //左2
			{
				*tx = a->px - 2; *ty = a->py;
				*tx++; *ty++; *tc += 1;
			}
			if (checkfield(a->px, a->py - 2) == 1)
			if(map[a->py-1][a->px][0]!=1)
			if (teamcheck(map[a->py][a->px][1], map[a->py-2][a->px][1]) == 1)  //上2
			{
				*tx = a->px; *ty = a->py - 2;
				*tx++; *ty++; *tc += 1;
			}
			if (checkfield(a->px, a->py + 2) == 1)
			if (map[a->py + 1][a->px][0] != 1)
			if (teamcheck(map[a->py][a->px][1], map[a->py+2][a->px][1]) == 1)  //下2
			{
				*tx = a->px; *ty = a->py + 2;
				*tx++; *ty++; *tc += 1;
			}
		}
}

int attack(void *x, void *y, int *tx, int *ty, int cout)
{
	srand((unsigned)time(NULL));
	int erb; //eは選んだ番号
	int tar;
	int tempdefp;
	int tempdefm;
	int tempatt;
	int miss = 5;
	//命中判定------>4d3 6+sa以下--->ミス 6+sa以上=----->あたる sa----->地形の差----->原と部屋は2/-2 川を越えるは1//後でやる(
	struct unitdata *a,*b;//aとxは攻撃する側、bとyは攻撃される側

	a = (struct unitdata*)x;
	b = (struct unitdata*)y;


	scanfwild(&erb, 1, cout);


	if (erb == 0)
		return 0;

	erb--;
	tar = map[*(ty + erb)][*(tx + erb)][1];
	if (tar > 4)
		tar -= 5;
	else
		tar--;

	//一時データにデータを与える
	tempdefp = (b + tar)->phdef;
	tempdefm = (b + tar)->magicdef;
	tempatt = a->att;

	defendup(&tempdefp, &tempdefm, &miss, (b + tar)->px, (b + tar)->py, (b + tar)->skill);
	attup(&tempatt, a->skill);

	if (ra(4, d3) <= miss)
	{
		printf("ミス\n");
		return 0;
	}

	printf("%sは%sに", a->name, (b + tar)->name);
	hithim(a->atttype, tempatt, tempdefp, tempdefm, &(b + tar)->hp);

	if ((b + tar)->hp <= 0)
	{
		printf("%sは死んだ。\n", (b + tar)->name);
		map[(b + tar)->py][(b + tar)->px][1] = 0;
		(b + tar)->px = 0;
		(b + tar)->py = 0;
		(b + tar)->hp = 0;
		return 1;
	}
	return 0;
}
//状態変更
void defendmode(int *x)
{
	*x = 1;
}
//パソコン側の行動
int pcattack(void *x, void *y, int *tx, int *ty, int cout)
{
	srand((unsigned)time(NULL));
	int tar=0;
	int tempdefp,ctempdefp=0;
	int tempdefm,ctempdefm=0;
	int tempatt;
	int miss = 5;
	int highest=0;
	int htn;
	int i;
	int tempdam;
	//命中判定------>4d3 6+sa以下--->ミス 6+sa以上=----->あたる sa----->地形の差----->原と部屋は2/-2 川を越えるは1//後でやる(
	struct unitdata *a, *b;//aとxは攻撃する側、bとyは攻撃される側

	a = (struct unitdata*)x;
	b = (struct unitdata*)y;

	//一時データにデータを与える
	tempatt = a->att;

	attup(&tempatt, a->skill);

	for (i = 0; i <= cout-1; ++i)
	{
		tempdefp = (b + i)->phdef;
		tempdefm = (b + i)->magicdef;

		defendup(&tempdefp, &tempdefm, &miss, (b + i)->px, (b + i)->py, (b + i)->skill);
	
		if (typeret(a->atttype) == 2)
			tempdam = tempatt - tempdefp;
		if (typeret(a->atttype) == 1)
			tempdam = tempatt - tempdefp;

		if (tempdam > (b + i)->hp)
		{
			htn = i;
			ctempdefm = tempdefm;
			ctempdefp = tempdefp;
			break;
		}

		if (tempdam > highest)
		{
			htn = i;
			ctempdefm = tempdefm;
			ctempdefp = tempdefp;
		}
	}

	tar = map[*(ty + htn)][*(tx + htn)][1];
	if (tar > 4)
		tar -= 5;
	else
		tar--;

	if (ra(4, d3) <= miss)
	{
		printf("ミス\n");
		return 0;
	}

	printf("%sは%sに", a->name, (b + tar)->name);
	hithim(a->atttype, tempatt, ctempdefp, ctempdefm, &(b + tar)->hp);

	if ((b + tar)->hp <= 0)
	{
		printf("%sは死んだ。\n", (b + tar)->name);
		map[(b + tar)->py][(b + tar)->px][1] = 0;
		(b + tar)->px = 0;
		(b + tar)->py = 0;
		(b + tar)->hp = 0;
		return 1;
	}
	return 0;
}

//防御アップ関連
void defendup(int *dp, int *dm,int *miss, int x, int y, int status)
{
	if (map[y][x][0] == 3)//部屋にいる
	{
		*dp += 2;
		*miss += 1;
		*dm += 2;
	}
	if (map[y][x][0] == 5)//橋にいる
	{
		*dp -= 2;
		*miss -= 1;
		*dm -= 2;
	}
	if (status == 1)//defendmode
	{
		*dp += 3;
		*miss += 1;
		*dm += 3;
	}
	if (map[y][x][0] == 6)//森にいる
	{
		*miss += 2;
	}
	if (status == 2)//defendup
	{
		*dp += 4;
		*dm += 4;
	}
}

void attup(int *att, int status)
{
	if (status == 3)//attackup
	{
		*att += 4;
	}
}

void hithim(int attype, int att, int dp, int dm, int *hp)
{
	//攻撃動作
	if (typeret(attype) == 2 && att > dp)
	{
		printf("%d物理ダメージを与えた。\n", att - dp);
		*hp -= att - dp;
	}
	if (typeret(attype) == 2 && att <= dp)
	{
		printf("1物理ダメージを与えた。\n");
		*hp -= 1;
	}
	if (typeret(attype) == 1 && att > dm)
	{
		printf("%d魔法ダメージを与えた。\n", att - dm);
		*hp -= att - dm;
	}
	if (typeret(attype) == 1 && att <= dm)
	{
		printf("0魔法ダメージを与えた。\n");
	}
}

//治療部分
void healshow(void *x, int *tx, int *ty, int *tc)
{
	struct unitdata *a;

	a = (struct unitdata*)x;

	*tx = a->px; *ty = a->py;
	*tx++; *ty++; *tc += 1;

	if (checkfield(a->px + 1, a->py) == 1)
		if (teamcheck(map[a->py][a->px][1], map[a->py][a->px + 1][1]) == 2) //右
		{
			*tx = a->px + 1; *ty = a->py;
			*tx++; *ty++; *tc += 1;
		}
	if (checkfield(a->px - 1, a->py) == 1)
		if (teamcheck(map[a->py][a->px][1], map[a->py][a->px - 1][1]) == 2) //左
		{
			*tx = a->px - 1; *ty = a->py;
			*tx++; *ty++; *tc += 1;
		}
	if (checkfield(a->px, a->py - 1) == 1)
		if (teamcheck(map[a->py][a->px][1], map[a->py - 1][a->px][1]) == 2) //上
		{
			*tx = a->px; *ty = a->py - 1;
			*tx++; *ty++; *tc += 1;
		}
	if (checkfield(a->px, a->py + 1) == 1)
		if (teamcheck(map[a->py][a->px][1], map[a->py + 1][a->px][1]) == 2) //下
		{
			*tx = a->px; *ty = a->py + 1;
			*tx++; *ty++; *tc += 1;
		}
}

void heal(void *x, void *y, int *tx, int *ty, int cout) //ai側を使うときはint型に変わる
{
	int erb; //eは選んだ番号
	int tar;
	struct unitdata *a, *b;//aとxは攻撃する側、bとyは攻撃される側

	a = (struct unitdata*)x;
	b = (struct unitdata*)y;

	scanfwild(&erb, 1, cout);

	if (erb == 0)
		return;

	erb--;
	tar = map[*(ty + erb)][*(tx + erb)][1];
	if (tar > 4)
		tar -= 5;//構造体はいずれの１番から指せるから、もう１個前に進む
	else
		tar--;

	erb = 0;

	if (a->type == 7)
	{
		printf("1.治療 2.防御アップ 3.攻撃アップ:");
		scanfwild(&erb, 1, 3);
	}

	if (erb == 2)
	{
		(b + tar)->skill = 2;
		printf("%sの防御力が上がりました\n", (b + tar)->name);
	}

	if (erb == 3)
	{
		(b + tar)->skill = 3;
		printf("%sの攻撃力が上がりました\n", (b + tar)->name);
	}

	if (a->type != 7 || erb == 1)
	{
		if (a == (b + tar) && a->recovery / 2 < (b + tar)->maxhp - (b + tar)->hp)
		{
			printf("%sは%sに%dHPを回復しました。\n", a->name, (b + tar)->name, a->recovery / 2);
			(b + tar)->hp += a->recovery / 2;
			return;
		}

		if (a == (b + tar) && a->recovery / 2 < (b + tar)->maxhp - (b + tar)->hp)
		{
			printf("%sは%sに%dHPを回復しました。\n", a->name, (b + tar)->name, (b + tar)->maxhp - (b + tar)->hp);
			(b + tar)->hp = (b + tar)->maxhp;
			return;
		}

		if (a->recovery < (b + tar)->maxhp - (b + tar)->hp)
		{
			printf("%sは%sに%dHPを回復しました。\n", a->name, (b + tar)->name, a->recovery);
			(b + tar)->hp += a->recovery;
		}
		else
		{
			printf("%sは%sに%dHPを回復しました。\n", a->name, (b + tar)->name, (b + tar)->maxhp - (b + tar)->hp);
			(b + tar)->hp = (b + tar)->maxhp;
		}
	}
	return;
}

int showmove(void *x) //showmove関数を使った後、必ずmove関数を使う　//この関数は便利操作表す用
{
	int i = 0;
	struct unitdata *a;
	a = (struct unitdata*)x; //目標の座標を読む


	if (tf(map[a->py][a->px - 1][0]) == 1 && (a->px - 1) >= 1 && map[a->py][a->px - 1][1] == 0) //四方向へ移動できるかどうかの確認//地形確認、例外チェック、ホルダーチェック
	{
		map[a->py][a->px - 1][3] = 1;
		++i;
	}
	if (tf(map[a->py + 1][a->px][0]) == 1 && (a->py + 1) <= 8 && map[a->py + 1][a->px][1] == 0)
	{
		map[a->py + 1][a->px][3] = 2;
		++i;
	}
	if (tf(map[a->py][a->px + 1][0]) == 1 && (a->px + 1) <= 10 && map[a->py][a->px + 1][1] == 0)
	{
		map[a->py][a->px + 1][3] = 3;
		++i;
	}
	if (tf(map[a->py - 1][a->px][0]) == 1 && (a->py - 1) >= 1 && map[a->py - 1][a->px][1] == 0)
	{
		map[a->py - 1][a->px][3] = 4;
		++i;
	}
	if (i != 0)
		return 1;
	else
		return 0;
}

int tf(int x) //目標地の地形の判断
{
	if (x == 0 || x == 3 || x == 5 || x == 6)
		return 1;
	else
		return 0;
}

void movem(void *x, int y) //移動指示
{
	int choose = 1;
	struct unitdata *a;
	a = (struct unitdata*)x;

	if (y != 0)
	{
		printf("行きたいところの番号を入力してください(0は移動をスキップ)：");

		while (1)
		{
			scanf_s("%d", &choose);

			if (choose == 1 && map[a->py][a->px - 1][3] == 0)
				choose = 5;
			if (choose == 2 && map[a->py + 1][a->px][3] == 0)
				choose = 5;
			if (choose == 3 && map[a->py][a->px + 1][3] == 0)
				choose = 5;
			if (choose == 4 && map[a->py - 1][a->px][3] == 0)
				choose = 5;
			if (choose >= 0 && choose <= 4)
				break;
			else
				printf("正し番号を入力してください:");//いけない選択肢を選ぶときは５を返してもう一度入力
		} //1から4を選択
	}
	if (a->px - 1 >= 1)
		map[a->py][a->px - 1][3] = 0;//指令用一時データを削除
	if (a->py + 1 <= 8)
		map[a->py + 1][a->px][3] = 0;
	if (a->px + 1 <= 10)
		map[a->py][a->px + 1][3] = 0;
	if (a->py - 1 >= 1)
		map[a->py - 1][a->px][3] = 0;

	if (y == 0)
	{
		printf("移動できない。\n");
		getchar(); getchar();
		return;
	}

	if (choose == 0)
		return;


	switch (choose)
	{
	case 1:if (tf(map[a->py][a->px - 1][0]) == 1 && (a->px - 1) >= 1)//移動行為を完成//左へ
	{
		map[a->py][a->px - 1][1] = map[a->py][a->px][1];
		map[a->py][a->px][1] = 0;
		a->px -= 1;
		break;
	}
	case 2:if (tf(map[a->py + 1][a->px][0]) == 1 && (a->py + 1) <= 8)//下へ
	{
		map[a->py + 1][a->px][1] = map[a->py][a->px][1];
		map[a->py][a->px][1] = 0;
		a->py += 1;
		break;
	}
	case 3:if (tf(map[a->py][a->px + 1][0]) == 1 && (a->px + 1) <= 10)//右へ
	{
		map[a->py][a->px + 1][1] = map[a->py][a->px][1];
		map[a->py][a->px][1] = 0;
		a->px += 1;
		break;
	}
	case 4:if (tf(map[a->py - 1][a->px][0]) == 1 && (a->py - 1) >= 1)//上へ
	{
		map[a->py - 1][a->px][1] = map[a->py][a->px][1];
		map[a->py][a->px][1] = 0;
		a->py -= 1;
		break;
	}
	}
}