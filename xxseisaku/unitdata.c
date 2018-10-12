#include"game.h"
#define magic "魔法使い"//魔法ダメージを出すが、近距離と遠距離二種類がある//ランダムで//近距離のほうの体がより丈夫		
#define archer "射手" //一個の目を越えて攻撃ができる
#define warrior "戦士" //
#define priest "牧師" //回復役
#define lancer "槍使い" //斜線攻撃ができる戦士(hpは戦士より低いが、攻撃力がたかい)
#define paladin "騎士"//防御力が高い
#define jongleur "吟遊詩人"//buff
void showunitdata(void *x, int cout);
void unitdesign(void *x);

void randomdata(void *x,int y,int z,int p)
{
	int choose;
	struct unitdata *pt;

	pt = (struct unitdata*)x;

	pt->att = 5;
	pt->hp = 15;
	pt->maxhp = 15;
	pt->magicdef = 2;
	pt->phdef = 2;
	pt->range = 1;
	pt->move = 1;
	pt->atttype = 1;//1->四方向1コマ物理 2->八方向１コマ、四方向２コマ物理 3->八方向１コマ物理 4->八方向１コマ魔法 5->八方向１コマ、四方向２コマ魔法
	pt->recovery = 2;
	pt->skill = 0;

//	system("cls");

	if (p == 1)
	{
		printf("1は魔法使い(遠距離魔法攻撃タイプ)\n");
		printf("2は射手(遠距離物理攻撃タイプ)\n");
		printf("3は戦士(近距離物理攻撃タイプ)\n");
		printf("4は牧師(近距離斜線攻撃ができる魔法攻撃タイプ、HP回復量も高い)\n");
		printf("5は槍使い(近距離斜線攻撃ができる物理攻撃タイプ)\n");
		printf("6は騎士(近距離物理攻撃タイプ、防御力が高い)\n");
		printf("7は吟遊詩人(強化スキール持つ)\n");
		printf("8はユニットを作る\n");
		if (z == 1)
			printf("チームAの");
		if (z == 2)
			printf("チームBの");
		printf("ユニット%dのタイプを選んでください:", y);
		scanfwild(&choose, 1, 8);
	}
	if (p == 2)
	{
		srand((unsigned)time(NULL));
		choose = rand() % 7 + 1;
	}

	switch (choose)
	{
	case 1:strcpy_s(pt->name, 20, magic); hprand(&pt->hp, &pt->maxhp, 2, d3); pt->magicdef += ra(1, d3); pt->att += ra(3, d3); pt->atttype = 5; pt->type = 1; break;
	case 2:strcpy_s(pt->name, 20, archer); hprand(&pt->hp, &pt->maxhp, 2, d3); pt->att += ra(3,d3); pt->atttype=2;; pt->phdef--; pt->magicdef--; pt->type = 2; break;
	case 3:strcpy_s(pt->name, 20, warrior); hprand(&pt->hp, &pt->maxhp, 4, d6); pt->phdef += ra(1,d3); pt->att += ra(2,d3); pt->type = 3; break;
	case 4:strcpy_s(pt->name, 20, priest); hprand(&pt->hp, &pt->maxhp, 4, d3); pt->att += ra(1, d3); pt->magicdef += ra(1, d3);  pt->atttype = 4; pt->recovery += ra(1, d6); pt->type = 4; break;
	case 5:strcpy_s(pt->name, 20, lancer); hprand(&pt->hp, &pt->maxhp, 4, d3);  pt->att += ra(2, d4); pt->atttype = 3; pt->type = 5; break;
	case 6:strcpy_s(pt->name, 20, paladin); hprand(&pt->hp, &pt->maxhp, 4, d6); pt->magicdef += ra(1, d4); pt->move++; pt->phdef += ra(1, d4); pt->att += ra(1, d3); pt->type = 6; break;
	case 7:strcpy_s(pt->name, 20, jongleur); hprand(&pt->hp, &pt->maxhp, 2, d4); pt->magicdef += ra(1, d3), pt->att += ra(1, d3); pt->recovery += ra(1, d4); pt->type = 7,pt->atttype=4; break;
	case 8:unitdesign(x);
	}
	return;
}

void unitdesign(void *x)
{
	int count;
	int inpu1, inpu2;
	int temper;
	struct unitdata *pt;

	pt = (struct unitdata*)x;

	pt->att = 5;
	pt->hp = 15;
	pt->maxhp = 15;
	pt->magicdef = 2;
	pt->phdef = 2;
	pt->range = 1;
	pt->move = 1;
	pt->atttype = 1;//1->四方向1コマ物理 2->八方向１コマ、四方向２コマ物理 3->八方向１コマ物理 4->八方向１コマ魔法 5->八方向１コマ、四方向２コマ魔法
	pt->recovery = 2;
	pt->skill = 0;

	count = 8;

	system("cls");
	printf("ユニットの名前を入力してください。(4文字以内)");
	scanf_s("%s", &pt->name, 20);
	printf("ユニットの攻撃タイプを選んでください。\n・物理は1、魔法は２。");
	scanfwild(&inpu1, 1, 2);
	if (inpu1 == 1)
	{
		printf("攻撃範囲を選んでください。\n四方向１コマは1、八方向１コマは2、四方向2コマは3。");
		scanfwild(&inpu2, 1, 3);
		if (inpu2 == 1)pt->atttype = 1;
		if (inpu2 == 2)pt->atttype = 3;
		if (inpu2 == 3)pt->atttype = 2;
	}
	if (inpu1 == 2)
	{
		printf("攻撃範囲を選んでください。\n八方向１コマは1、四方向2コマは2。");
		scanfwild(&inpu2, 1, 2);
		if (inpu2 == 1)pt->atttype = 4;
		if (inpu2 == 2)pt->atttype = 5;
	}
	printf("行動力を選んでください。1回/ターンは1,2回/ターンは2。(2はチケット2個消費)");
	scanfwild(&inpu1, 1, 2);
	if (inpu1 == 2)
	{
		count -= 2;
		pt->move = 2;
	}

	srand((unsigned)time(NULL));

	while (count > 0)
	{
		showunitdata(x, count);
		printf("攻撃力をアップするは1\n");
		printf("H    Pをアップするは2\n");
		printf("物理防御力をアップするは3\n");
		printf("魔法防御力をアップするは4\n");
		printf("回復力をアップするは5\n");
		scanfwild(&inpu1, 1, 5);
		temper = rand() % 3;
		if (inpu1 == 1)
			pt->att += 2 * temper;
		if (inpu1 == 2)
			pt->hp = (pt->maxhp += 4 * temper);
		if (inpu1 == 3)
			pt->phdef += temper;
		if (inpu1 == 4)
			pt->magicdef += temper;
		if (inpu1 == 5)
			pt->recovery += temper;
		--count;
	}
}

void showunitdata(void *x, int cout)
{
	system("cls");
	struct unitdata *pt;
	pt = (struct unitdata*)x;
	printf("名前:%s\n", pt->name);
	printf("H  P:%d\n", pt->maxhp);
	if (typeret(pt->atttype) == 1);
	printf("物理攻撃\n");
	printf("攻撃力:%d\n", pt->att);
	printf("物理防御力:%d\n", pt->phdef);
	printf("魔法防御力:%d\n", pt->magicdef);
	printf("回  復  力:%d\n", pt->recovery);
	printf("残ったチケット:%d\n \n", cout);
}