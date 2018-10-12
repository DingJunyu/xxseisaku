#include"game.h"

int ra(int x, int y)// x dx を実現
{
	int ov = 0;
	int i;
	srand((unsigned)time(NULL));
	for (i = 1; i <= x; ++i)
		ov += (rand() % y + 1);
	return ov;
}

void reset()
{
	int i, j;
	for (i = 0; i <= 8; ++i)
		for (j = 0; j <= 10; ++j)
			map[i][j][0] = map[i][j][1] = map[i][j][2] = map[i][j][3] = 0;
	return;
}

int checkfield(int x, int y)
{
	if (x >= 1 && x <= 10 && y >= 1 && y <= 8)
		return 1;
	return 0;
}

int teamcheck(int x, int y)
{
	if (y == 0)
		return 0;
	if ((x >= 1 && x <= 4 && y >= 5 && y <= 8) || (y >= 1 && y <= 4 && x >= 5 && x <= 8))
		return 1;
	if ((x >= 1 && x <= 4 && y >= 1 && y <= 4) || (x >= 5 && x <= 8 && y >= 5 && y <= 8))
		return 2;
	return 0;
}

void readmap(int x)
{
	int i, j;
	char filename[100];
	sprintf_s(filename,100, ".//mapdata//map%d.txt", x);
	FILE *mpr;
	fopen_s(&mpr,filename, "r");

	for (i = 1; i <= 8; ++i)
		for (j = 1; j <= 10; ++j)
		{
			fscanf_s(mpr, "%1d", &map[i][j][0]);
		}
	fclose(mpr);
}


int typeret(int x) //魔法は１、物理は２
{
	if (x == 1 || x == 2 || x == 3)
		return 2;
	if (x == 4 || x == 5)
		return 1;
	return 0;
}

void scanfwild(int *x, int a, int b)
{
	*x = a;
	while(1)
	{
		scanf_s("%d", x);

		if (*x >= a && *x <= b)
			break;

		else
			printf("正し番号を入力してください:");

	}

}

void hprand(int *x, int *y, int a, int b)
{
	*x += ra(a, b);
	*y = *x;
}

void resetunit(void *x)
{
	struct unitdata *pt;

	char voidname[20] = "未決定";

	pt = (struct unitdata*)x;

	pt->hp = 0;
	pt->maxhp = 0;
	pt->skill = 0;
	strcpy_s(pt->name, 20, voidname);
}

void roundshow(int x, int y)
{
	if (x > 4)
		printf("A");
	else
		printf("B");
	printf("チームの%d番の出番だ\n", y + 1);
}