#include"game.h"
int check1(int, int, int);//重みチェック
int check2(int, int, int);//チームチェック
int putthewayback(int ct, int x, int y);
int returnthemback(int x, int y, int mynum, int ct, int list1, int *tx, int *ty, int *counter);

int myturn(int *r, void *me, void *target, int *res)
{
	int tary[5];
	int tarx[5];
	int tarc = 0;
	int inpu1 = 0, inpu2 = 0;
	int j;
	int mark = 0;
	int canyoumove;
	int cout=0;

	struct unitdata *a, *b;

	a = (struct unitdata*)me;
	b = (struct unitdata*)target;

	if (*res <= 0)
		return 1;

	canyoumove = a->move;

	j = *r - 5;
	*r -= 4;

	if ((a + j)->hp <= 0)//ターゲットは死んだ場合はターンをスキップ
		return 2;

	attshow(a + j, &tarx[1], &tary[1], &tarc);
	if (tarc != 0)
	{
		*res -= pcattack(a + j, b, &tarx[1], &tary[1], tarc);
		rewind(stdin);
		getchar();
		if (*res == 0)//敵が全部死んだらおわり
			return 1;
		return 0;
	}

	while (tarc == 0)
	{
		resetmyway();
		if (findmyway((a + j)->px, (a + j)->py, j + 5, 1, 1) != 1)
			break;
		checker = 0;
		if (checkfield(way[1][1], way[1][0]) == 1)
		{
			map[(a + j)->py][(a + j)->px][1] = 0;
			(a + j)->px = way[1][1];
			(a + j)->py = way[1][0];
			map[(a + j)->py][(a + j)->px][1] = j + 5;
			printf("Bチームの%d番はx:%d y:%dに行きました。\n", j + 1, (a + j)->px, (a + j)->py);
		}
		++cout;
		if (cout == canyoumove || map[(a + j)->py][(a + j)->px][0] == 6)
			break;
	}
	attshow(a + j, &tarx[1], &tary[1], &tarc);
	if (tarc != 0)
	{
		kansushow(a, b, *r);
		*res -= pcattack(a + j, b, &tarx[1], &tary[1], tarc);
		rewind(stdin);
		getchar();
		if (*res <= 0)//敵が全部死んだらおわり
			return 1;
		return 0;
	}
	rewind(stdin);
	getchar();
	return 0;
}


int findmyway(int x, int y, int mynum, int ct, int mount)
{
	/*繰り返す用変数*/
	int i;
	/*回数記録*/
	int counter = 1;
	/*全体変数のデータを保存*/
	int tempx[64], tempy[64];
	/*行ける場所がない場合、関数を止まるための変数*/
	int action = 0;
	/*ルートを返す時用変数*/
	int temp;
	if (mount == 1)
	{
		muchx[1] = x;
		muchy[1] = y;
	}
	for (i = 1; i <= mount; i++)
	{
		tempx[i] = muchx[i];
		tempy[i] = muchy[i];
	}

	for (i = 1; i <= mount; i++)
	{
		/*四方向へ探す*/
		if (map[tempy[i]][tempx[i]][2] == ct - 1 || ct == 1)
		{
			temp = returnthemback(tempx[i] - 1, tempy[i], mynum, ct, i, muchx, muchy, &counter);
			if (temp == 1)
				return 1;
			if (temp == 2)
				++action;
			temp = returnthemback(tempx[i] + 1, tempy[i], mynum, ct, i, muchx, muchy, &counter);
			if (temp == 1)
				return 1;
			if (temp == 2)
				++action;
			temp = returnthemback(tempx[i], tempy[i] - 1, mynum, ct, i, muchx, muchy, &counter);
			if (temp == 1)
				return 1;
			if (temp == 2)
				++action;
			temp = returnthemback(tempx[i], tempy[i] + 1, mynum, ct, i, muchx, muchy, &counter);
			if (temp == 1)
				return 1;
			if (temp == 2)
				++action;
		}
		if (i == mount)
			break;
	}
	/*次の段階に入らない場合は0を返す*/
	if (action == 0)
		return 0;
	/*結果を見つけたっら1を返し、上の層に戻る*/
	if (findmyway(muchx[1], muchy[1], mynum, ct + 1, counter) == 1)
		return 1;
	return 0;
}

void resetmyway()
{
	int i, j;
	for (i = 0; i <= 8; ++i)
		for (j = 0; j <= 10; ++j)
		{
			map[i][j][2] = 999;
		}
	for (i = 1; i <= 64; ++i)
	{
		way[i][0] = way[i][1] = 0;
	}
}

/*check1関数*/
/*次のコマに移動できる判定*/
/*できる場合は0を返す*/
/*できない場合（山、川、壁、同じチームのユニットがある）は1を返す*/
int check1(int x, int y, int ct)//移動できる判定１--->地形
{
	if (map[y][x][0] != 1 && map[y][x][0] != 2 && map[y][x][0] != 4 && map[y][x][2] > ct)
		return 1;
	else
		return 0;
}

/*check2関数*/
/*次のコマのいるものは敵かどうかの判定*/
/*敵の場合は1を返す*/
int check2(int x, int y, int mynum)//敵判定
{
	if (map[y][x][1] != 0 && teamcheck(mynum, map[y][x][1]) == 1)
		return 1;
	else
		return 0;
}

/*putthewayback関数*/
/*ct:移動順番の番号*/
/*終点から起点の座標を記録*/
int putthewayback(int ct, int x, int y)
{
	if (x == 999)
		return 0;
	if (x != 999 && y != 999)
	{
		way[ct][0] = y; way[ct][1] = x;
	}
	if (ct == 1)
		return 1;
	if (checkfield(x - 1, y) == 1)
		if (map[y][x - 1][2] < ct)
		{
			if (putthewayback(ct - 1, x - 1, y) == 1)
				return 1;
		}
	if (checkfield(x + 1, y) == 1)
		if (map[y][x + 1][2] < ct)
		{
			if (putthewayback(ct - 1, x + 1, y) == 1)
				return 1;
		}
	if (checkfield(x, y - 1) == 1)
		if (map[y - 1][x][2] < ct)
		{
			if (putthewayback(ct - 1, x, y - 1) == 1)
				return 1;
		}
	if (checkfield(x, y + 1) == 1)
		if (map[y + 1][x][2] < ct)
		{
			if (putthewayback(ct - 1, x, y + 1) == 1)
				return 1;
		}
	return 0;
}

void showmethemap()//デバッグ用--->ルート探す
{
	int i, j;
	for (i = 1; i <= 8; i++)
	{
		for (j = 1; j <= 10; j++)
			printf("%3d ", map[i][j][2]);
		printf("\n");
	}
	printf("\n");
	getchar();
}

/*returnthemback関数*/
/*今の位置への移動が可能かを判断し、もし終点はここにあれば、ルートを保存しつつ、上の層に戻ります*/
/*入力値*/
/*x,y:座標 mynum:ユニット番号 ct:今の層数*/
/*list番号*/
/*tx,ty:保存用配列*/
/*counter:統計値*/
int returnthemback(int x, int y, int mynum, int ct, int list1, int *tx, int *ty, int *counter)
{
	if (checkfield(x, y) == 1 && check1(x, y, ct) == 1 && (check2(x, y, mynum) == 1 || map[y][x][1] == 0))
	{
		map[y][x][2] = ct;
		*(tx + *counter) = x;
		*(ty + *counter) = y;
		*counter += 1;
		++checker;
		if (teamcheck(mynum, map[y][x][1]) == 1)
		{
			putthewayback(ct, x, y);
			return 1;
		}
		return 2;
	}
	return 0;
}