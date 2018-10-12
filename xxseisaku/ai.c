#include"game.h"
int check1(int, int, int);//�d�݃`�F�b�N
int check2(int, int, int);//�`�[���`�F�b�N
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

	if ((a + j)->hp <= 0)//�^�[�Q�b�g�͎��񂾏ꍇ�̓^�[�����X�L�b�v
		return 2;

	attshow(a + j, &tarx[1], &tary[1], &tarc);
	if (tarc != 0)
	{
		*res -= pcattack(a + j, b, &tarx[1], &tary[1], tarc);
		rewind(stdin);
		getchar();
		if (*res == 0)//�G���S�����񂾂炨���
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
			printf("B�`�[����%d�Ԃ�x:%d y:%d�ɍs���܂����B\n", j + 1, (a + j)->px, (a + j)->py);
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
		if (*res <= 0)//�G���S�����񂾂炨���
			return 1;
		return 0;
	}
	rewind(stdin);
	getchar();
	return 0;
}


int findmyway(int x, int y, int mynum, int ct, int mount)
{
	/*�J��Ԃ��p�ϐ�*/
	int i;
	/*�񐔋L�^*/
	int counter = 1;
	/*�S�̕ϐ��̃f�[�^��ۑ�*/
	int tempx[64], tempy[64];
	/*�s����ꏊ���Ȃ��ꍇ�A�֐����~�܂邽�߂̕ϐ�*/
	int action = 0;
	/*���[�g��Ԃ����p�ϐ�*/
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
		/*�l�����֒T��*/
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
	/*���̒i�K�ɓ���Ȃ��ꍇ��0��Ԃ�*/
	if (action == 0)
		return 0;
	/*���ʂ�����������1��Ԃ��A��̑w�ɖ߂�*/
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

/*check1�֐�*/
/*���̃R�}�Ɉړ��ł��锻��*/
/*�ł���ꍇ��0��Ԃ�*/
/*�ł��Ȃ��ꍇ�i�R�A��A�ǁA�����`�[���̃��j�b�g������j��1��Ԃ�*/
int check1(int x, int y, int ct)//�ړ��ł��锻��P--->�n�`
{
	if (map[y][x][0] != 1 && map[y][x][0] != 2 && map[y][x][0] != 4 && map[y][x][2] > ct)
		return 1;
	else
		return 0;
}

/*check2�֐�*/
/*���̃R�}�̂�����͓̂G���ǂ����̔���*/
/*�G�̏ꍇ��1��Ԃ�*/
int check2(int x, int y, int mynum)//�G����
{
	if (map[y][x][1] != 0 && teamcheck(mynum, map[y][x][1]) == 1)
		return 1;
	else
		return 0;
}

/*putthewayback�֐�*/
/*ct:�ړ����Ԃ̔ԍ�*/
/*�I�_����N�_�̍��W���L�^*/
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

void showmethemap()//�f�o�b�O�p--->���[�g�T��
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

/*returnthemback�֐�*/
/*���̈ʒu�ւ̈ړ����\���𔻒f���A�����I�_�͂����ɂ���΁A���[�g��ۑ����A��̑w�ɖ߂�܂�*/
/*���͒l*/
/*x,y:���W mynum:���j�b�g�ԍ� ct:���̑w��*/
/*list�ԍ�*/
/*tx,ty:�ۑ��p�z��*/
/*counter:���v�l*/
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