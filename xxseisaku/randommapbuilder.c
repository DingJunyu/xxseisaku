#include"game.h"
int randomplace();
void randomnum(int *, int, int,int);
void maketheriver();
void putthisinthemap(int x,int which);
void findbridge();
void putthebridge(int x);
#define currentpos map[y1][x1]
//これから---->マップをもっと自然のようにしよう！

void randommap()
{
	int tar;
	srand((unsigned)time(NULL));
	reset();
	int all;
	int i, j;
	
	int numofmountains=0;
	tar= rand() % 1000;
	randomnum(&numofmountains, tar, 1000,0);
	putthisinthemap(numofmountains,1);

	int numofwater=0;
	tar = rand() % 1000;
	if (tar <= 400)
	{
		randomnum(&numofwater, tar, 400,0);
		putthisinthemap(numofwater, 2);
	}
	else
	{
		maketheriver();
		findbridge();
	}

	int numoftree;
	tar = rand() % 1000;
	randomnum(&numoftree,tar,1000,30);
	putthisinthemap(numoftree, 6);
	all = numofmountains + numofwater;
	for (i = 1; i <= 8; i++)
		for (j = 1; j <= 2; j++)
			if (map[i][j][0] != 1 && map[i][j][0] != 2)
				goto outtohere;
outtohere:
	resetmyway();
	findmyway(j, i, 1, 1, 1);
	if (all + checker <= 79)
	{
		for(i=1;i<=8;i++)
			for(j=1;j<=10;j++)
				if (map[i][j][2] == 999 && map[i][j][0] != 1 && map[i][j][0] != 2)
				{
					map[i + 1][j][0] = 0;
					map[i - 1][j][0] = 0; 
					map[i][j + 1][0] = 0; 
					map[i][j - 1][0] = 0;
				}
	}
	checker = 0;
	return;
}

int randomplace()
{
	int ans;
	srand((unsigned)time(NULL));
	ans = rand() % 100;
	if (ans > 50)
		return 1;
	else
		return 0;
	return 0;
}

/*randomnum ランダム関数*/
/*xは目標変数、ｙは範囲判定値、hanniは判定用数字、aは最小値*/
void randomnum(int *x,int y,int hanni,int a)
{
	srand((unsigned)time(NULL));
	if (y <= hanni / 10)
		*x = 0;
	else if(y<=(hanni/10)*5)
		*x = rand() % (6+a) + 2+a/3;
	else
		*x = rand() % (2+a) + 6+a/2;
}

void maketheriver()
{
	int column=1;
	int row = 1;
	int steps = 0;
	int stepsr = 0;
	int lfgo;
	int mark=0;
	srand((unsigned)time(NULL));
	int startpoint=0;
	startpoint = rand() % 3 + 4;
	row = startpoint;
	while (column <= 8)
	{
		map[column][row][0] = 2;
		mark = 0;
		if (row != startpoint)//横に行く
		{
			++stepsr;
			if (row < startpoint)
				--row;
			else
				++row;
			if (row >= 10 || row <= 0)
			{
				steps = 0;
				stepsr = 0;
			}
			if ((stepsr == 1 && randomplace() == 1) || stepsr == 2)//下へに戻る
			{
				steps = 0;
				stepsr = 0;
				startpoint = row;
				mark = 1;
			}
			if (stepsr < 2 && mark == 0)
				continue;
		}
		if ((steps == 2 && randomplace() == 1) || steps == 3)//横へに入る
		{
			if (randomplace() == 1)
			{
				++row;
				lfgo = 1;
			}
			else
			{
				--row;
				lfgo = 0;
			}
			if (lfgo == 1&& column>=4)
				row -= 2;
			if(lfgo==0&&column>=4)
				row += 2;
			if (row >= 10 || row <= 0)
			{
				steps = 0;
				stepsr = 0;
			}
			steps = 0; 
		}
		++steps;
		++column;
	}
}

void putthisinthemap(int x, int which)
{
	int i, j;
	srand((unsigned)time(NULL));
	while (x > 0)
	{
		i = rand() % 8 + 1;
		j = rand() % 10 + 1;
		if (map[i][j][0] == 0)
		{
			map[i][j][0] = which;
		}
		else
			continue;
		--x;
	}
}

void findbridge()
{
	srand((unsigned)time(NULL));
	int b1, b2, b3;
	b1 = rand() % 3 + 1;
	b2 = rand() % 3 + 4;
	putthebridge(b1);
	putthebridge(b2);
	if (b1 <= 3 && b2 >= 6)
	{
		b3 = rand() % 2 + 3;
		putthebridge(b3);
	}
}

void putthebridge(int x)
{
	int i;
	for(i=1;i<=10;++i)
		if (map[x][i][0] == 2)
		{
			map[x][i][0] = 5;
			if (map[x][i - 1][0] == 1)
				map[x][i - 1][0] = 0;
			if (map[x][i + 1][0] == 1)
				map[x][i + 1][0] = 0;
			break;
		}
}

void findtheposition(void *x, void *y)
{
	struct unitdata *a;
	struct unitdata *b;
	a = (struct unitdata*)x;
	b = (struct unitdata*)y;

	int i=1, j=1;
	int x1, y1;

	srand((unsigned)time(NULL));

	while (1)
	{
		x1 = rand() % 2 + 1;
		y1 = rand() % 8 + 1;
		if (currentpos[0] != 1 && currentpos[0] != 2 && currentpos[1] == 0)
		{
			a->px = x1; a->py = y1;
			currentpos[1] = i;
			++i;
			++a;
			if (i > 4)
				break;
		}
	}

	while (1)
	{
		x1 = rand() % 2 + 9;
		y1 = rand() % 8 + 1;
		if (currentpos[0] != 1 && currentpos[0] != 2 && currentpos[1] == 0)
		{
			b->px = x1; b->py = y1;
			currentpos[1] = j + 4;
			++j;
			++b;
			if (j > 4)
				break;
		}
	}
}