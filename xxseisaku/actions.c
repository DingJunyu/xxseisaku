#include"game.h"
void defendup(int *dp, int *dm, int *miss, int x, int y, int status);
void attup(int *att, int status);
void hithim(int attype, int att, int dp, int dm, int *hp);
int tf(int x);
//�U������
void attshow(void *x,int *tx,int *ty,int *tc)
{
	//��������------>4d3 6+sa�ȉ�--->�~�X 6+sa�ȏ�=----->������ sa----->�n�`�̍�----->���ƕ�����2/-2 ����z�����1
	struct unitdata *a;//a��x�͍U�����鑤�Ab��y�͍U������鑤

	a = (struct unitdata*)x;

		if (a->atttype == 3 || a->atttype == 4|| a->atttype == 2 || a->atttype == 5)
		{
			if(checkfield(a->px - 1,a->py-1)==1)
			if (teamcheck(map[a->py][a->px][1],map[a->py-1][a->px-1][1])==1) //����
			{
				*tx = a->px - 1; *ty = a->py - 1;
				*tx++; *ty++; *tc += 1;
			}
			if (checkfield(a->px + 1, a->py - 1) == 1)
			if (teamcheck(map[a->py][a->px][1],map[a->py - 1][a->px + 1][1])==1) //�E��
			{
				*tx = a->px + 1; *ty = a->py - 1;
				*tx++; *ty++; *tc += 1;
			}
			if (checkfield(a->px - 1, a->py + 1) == 1)
			if (teamcheck(map[a->py][a->px][1],map[a->py + 1][a->px - 1][1])==1) //����
			{
				*tx = a->px - 1; *ty = a->py + 1;
				*tx++; *ty++; *tc += 1;
			}
			if (checkfield(a->px + 1, a->py + 1) == 1)
			if (teamcheck(map[a->py][a->px][1], map[a->py + 1][a->px + 1][1]) == 1) //����
			{
				*tx = a->px + 1; *ty = a->py + 1;
				*tx++; *ty++; *tc += 1;
			}
		}

		if (checkfield(a->px + 1, a->py) == 1)
			if (teamcheck(map[a->py][a->px][1], map[a->py][a->px + 1][1]) == 1) //�E
			{
				*tx = a->px + 1; *ty = a->py;
				*tx++; *ty++; *tc += 1;
			}
		if (checkfield(a->px - 1, a->py) == 1)
			if (teamcheck(map[a->py][a->px][1], map[a->py][a->px - 1][1]) == 1) //��
			{
				*tx = a->px - 1; *ty = a->py;
				*tx++; *ty++; *tc += 1;
			}
		if (checkfield(a->px, a->py - 1) == 1)
			if (teamcheck(map[a->py][a->px][1], map[a->py - 1][a->px][1]) == 1) //��
			{
				*tx = a->px; *ty = a->py - 1;
				*tx++; *ty++; *tc += 1;
			}
		if (checkfield(a->px, a->py + 1) == 1)
			if (teamcheck(map[a->py][a->px][1], map[a->py + 1][a->px][1]) == 1) //��
			{
				*tx = a->px; *ty = a->py + 1;
				*tx++; *ty++; *tc += 1;
			}

		if (a->atttype == 2||a->atttype==5)
		{
			if (checkfield(a->px+2, a->py) == 1)
			if(map[a->py][a->px +1][0]!=1)
			if (teamcheck(map[a->py][a->px][1], map[a->py][a->px + 2][1]) == 1) //�E2
			{
				*tx = a->px + 2; *ty = a->py;
				*tx++; *ty++; *tc += 1;
			}
			if (checkfield( a->px-2,a->py) == 1)
			if(map[a->py][a->px - 1][0]!=1)
			if (teamcheck(map[a->py][a->px][1], map[a->py][a->px - 2][1]) == 1)  //��2
			{
				*tx = a->px - 2; *ty = a->py;
				*tx++; *ty++; *tc += 1;
			}
			if (checkfield(a->px, a->py - 2) == 1)
			if(map[a->py-1][a->px][0]!=1)
			if (teamcheck(map[a->py][a->px][1], map[a->py-2][a->px][1]) == 1)  //��2
			{
				*tx = a->px; *ty = a->py - 2;
				*tx++; *ty++; *tc += 1;
			}
			if (checkfield(a->px, a->py + 2) == 1)
			if (map[a->py + 1][a->px][0] != 1)
			if (teamcheck(map[a->py][a->px][1], map[a->py+2][a->px][1]) == 1)  //��2
			{
				*tx = a->px; *ty = a->py + 2;
				*tx++; *ty++; *tc += 1;
			}
		}
}

int attack(void *x, void *y, int *tx, int *ty, int cout)
{
	srand((unsigned)time(NULL));
	int erb; //e�͑I�񂾔ԍ�
	int tar;
	int tempdefp;
	int tempdefm;
	int tempatt;
	int miss = 5;
	//��������------>4d3 6+sa�ȉ�--->�~�X 6+sa�ȏ�=----->������ sa----->�n�`�̍�----->���ƕ�����2/-2 ����z�����1//��ł��(
	struct unitdata *a,*b;//a��x�͍U�����鑤�Ab��y�͍U������鑤

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

	//�ꎞ�f�[�^�Ƀf�[�^��^����
	tempdefp = (b + tar)->phdef;
	tempdefm = (b + tar)->magicdef;
	tempatt = a->att;

	defendup(&tempdefp, &tempdefm, &miss, (b + tar)->px, (b + tar)->py, (b + tar)->skill);
	attup(&tempatt, a->skill);

	if (ra(4, d3) <= miss)
	{
		printf("�~�X\n");
		return 0;
	}

	printf("%s��%s��", a->name, (b + tar)->name);
	hithim(a->atttype, tempatt, tempdefp, tempdefm, &(b + tar)->hp);

	if ((b + tar)->hp <= 0)
	{
		printf("%s�͎��񂾁B\n", (b + tar)->name);
		map[(b + tar)->py][(b + tar)->px][1] = 0;
		(b + tar)->px = 0;
		(b + tar)->py = 0;
		(b + tar)->hp = 0;
		return 1;
	}
	return 0;
}
//��ԕύX
void defendmode(int *x)
{
	*x = 1;
}
//�p�\�R�����̍s��
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
	//��������------>4d3 6+sa�ȉ�--->�~�X 6+sa�ȏ�=----->������ sa----->�n�`�̍�----->���ƕ�����2/-2 ����z�����1//��ł��(
	struct unitdata *a, *b;//a��x�͍U�����鑤�Ab��y�͍U������鑤

	a = (struct unitdata*)x;
	b = (struct unitdata*)y;

	//�ꎞ�f�[�^�Ƀf�[�^��^����
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
		printf("�~�X\n");
		return 0;
	}

	printf("%s��%s��", a->name, (b + tar)->name);
	hithim(a->atttype, tempatt, ctempdefp, ctempdefm, &(b + tar)->hp);

	if ((b + tar)->hp <= 0)
	{
		printf("%s�͎��񂾁B\n", (b + tar)->name);
		map[(b + tar)->py][(b + tar)->px][1] = 0;
		(b + tar)->px = 0;
		(b + tar)->py = 0;
		(b + tar)->hp = 0;
		return 1;
	}
	return 0;
}

//�h��A�b�v�֘A
void defendup(int *dp, int *dm,int *miss, int x, int y, int status)
{
	if (map[y][x][0] == 3)//�����ɂ���
	{
		*dp += 2;
		*miss += 1;
		*dm += 2;
	}
	if (map[y][x][0] == 5)//���ɂ���
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
	if (map[y][x][0] == 6)//�X�ɂ���
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
	//�U������
	if (typeret(attype) == 2 && att > dp)
	{
		printf("%d�����_���[�W��^�����B\n", att - dp);
		*hp -= att - dp;
	}
	if (typeret(attype) == 2 && att <= dp)
	{
		printf("1�����_���[�W��^�����B\n");
		*hp -= 1;
	}
	if (typeret(attype) == 1 && att > dm)
	{
		printf("%d���@�_���[�W��^�����B\n", att - dm);
		*hp -= att - dm;
	}
	if (typeret(attype) == 1 && att <= dm)
	{
		printf("0���@�_���[�W��^�����B\n");
	}
}

//���Õ���
void healshow(void *x, int *tx, int *ty, int *tc)
{
	struct unitdata *a;

	a = (struct unitdata*)x;

	*tx = a->px; *ty = a->py;
	*tx++; *ty++; *tc += 1;

	if (checkfield(a->px + 1, a->py) == 1)
		if (teamcheck(map[a->py][a->px][1], map[a->py][a->px + 1][1]) == 2) //�E
		{
			*tx = a->px + 1; *ty = a->py;
			*tx++; *ty++; *tc += 1;
		}
	if (checkfield(a->px - 1, a->py) == 1)
		if (teamcheck(map[a->py][a->px][1], map[a->py][a->px - 1][1]) == 2) //��
		{
			*tx = a->px - 1; *ty = a->py;
			*tx++; *ty++; *tc += 1;
		}
	if (checkfield(a->px, a->py - 1) == 1)
		if (teamcheck(map[a->py][a->px][1], map[a->py - 1][a->px][1]) == 2) //��
		{
			*tx = a->px; *ty = a->py - 1;
			*tx++; *ty++; *tc += 1;
		}
	if (checkfield(a->px, a->py + 1) == 1)
		if (teamcheck(map[a->py][a->px][1], map[a->py + 1][a->px][1]) == 2) //��
		{
			*tx = a->px; *ty = a->py + 1;
			*tx++; *ty++; *tc += 1;
		}
}

void heal(void *x, void *y, int *tx, int *ty, int cout) //ai�����g���Ƃ���int�^�ɕς��
{
	int erb; //e�͑I�񂾔ԍ�
	int tar;
	struct unitdata *a, *b;//a��x�͍U�����鑤�Ab��y�͍U������鑤

	a = (struct unitdata*)x;
	b = (struct unitdata*)y;

	scanfwild(&erb, 1, cout);

	if (erb == 0)
		return;

	erb--;
	tar = map[*(ty + erb)][*(tx + erb)][1];
	if (tar > 4)
		tar -= 5;//�\���̂͂�����̂P�Ԃ���w���邩��A�����P�O�ɐi��
	else
		tar--;

	erb = 0;

	if (a->type == 7)
	{
		printf("1.���� 2.�h��A�b�v 3.�U���A�b�v:");
		scanfwild(&erb, 1, 3);
	}

	if (erb == 2)
	{
		(b + tar)->skill = 2;
		printf("%s�̖h��͂��オ��܂���\n", (b + tar)->name);
	}

	if (erb == 3)
	{
		(b + tar)->skill = 3;
		printf("%s�̍U���͂��オ��܂���\n", (b + tar)->name);
	}

	if (a->type != 7 || erb == 1)
	{
		if (a == (b + tar) && a->recovery / 2 < (b + tar)->maxhp - (b + tar)->hp)
		{
			printf("%s��%s��%dHP���񕜂��܂����B\n", a->name, (b + tar)->name, a->recovery / 2);
			(b + tar)->hp += a->recovery / 2;
			return;
		}

		if (a == (b + tar) && a->recovery / 2 < (b + tar)->maxhp - (b + tar)->hp)
		{
			printf("%s��%s��%dHP���񕜂��܂����B\n", a->name, (b + tar)->name, (b + tar)->maxhp - (b + tar)->hp);
			(b + tar)->hp = (b + tar)->maxhp;
			return;
		}

		if (a->recovery < (b + tar)->maxhp - (b + tar)->hp)
		{
			printf("%s��%s��%dHP���񕜂��܂����B\n", a->name, (b + tar)->name, a->recovery);
			(b + tar)->hp += a->recovery;
		}
		else
		{
			printf("%s��%s��%dHP���񕜂��܂����B\n", a->name, (b + tar)->name, (b + tar)->maxhp - (b + tar)->hp);
			(b + tar)->hp = (b + tar)->maxhp;
		}
	}
	return;
}

int showmove(void *x) //showmove�֐����g������A�K��move�֐����g���@//���̊֐��͕֗�����\���p
{
	int i = 0;
	struct unitdata *a;
	a = (struct unitdata*)x; //�ڕW�̍��W��ǂ�


	if (tf(map[a->py][a->px - 1][0]) == 1 && (a->px - 1) >= 1 && map[a->py][a->px - 1][1] == 0) //�l�����ֈړ��ł��邩�ǂ����̊m�F//�n�`�m�F�A��O�`�F�b�N�A�z���_�[�`�F�b�N
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

int tf(int x) //�ڕW�n�̒n�`�̔��f
{
	if (x == 0 || x == 3 || x == 5 || x == 6)
		return 1;
	else
		return 0;
}

void movem(void *x, int y) //�ړ��w��
{
	int choose = 1;
	struct unitdata *a;
	a = (struct unitdata*)x;

	if (y != 0)
	{
		printf("�s�������Ƃ���̔ԍ�����͂��Ă�������(0�͈ړ����X�L�b�v)�F");

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
				printf("�����ԍ�����͂��Ă�������:");//�����Ȃ��I������I�ԂƂ��͂T��Ԃ��Ă�����x����
		} //1����4��I��
	}
	if (a->px - 1 >= 1)
		map[a->py][a->px - 1][3] = 0;//�w�ߗp�ꎞ�f�[�^���폜
	if (a->py + 1 <= 8)
		map[a->py + 1][a->px][3] = 0;
	if (a->px + 1 <= 10)
		map[a->py][a->px + 1][3] = 0;
	if (a->py - 1 >= 1)
		map[a->py - 1][a->px][3] = 0;

	if (y == 0)
	{
		printf("�ړ��ł��Ȃ��B\n");
		getchar(); getchar();
		return;
	}

	if (choose == 0)
		return;


	switch (choose)
	{
	case 1:if (tf(map[a->py][a->px - 1][0]) == 1 && (a->px - 1) >= 1)//�ړ��s�ׂ�����//����
	{
		map[a->py][a->px - 1][1] = map[a->py][a->px][1];
		map[a->py][a->px][1] = 0;
		a->px -= 1;
		break;
	}
	case 2:if (tf(map[a->py + 1][a->px][0]) == 1 && (a->py + 1) <= 8)//����
	{
		map[a->py + 1][a->px][1] = map[a->py][a->px][1];
		map[a->py][a->px][1] = 0;
		a->py += 1;
		break;
	}
	case 3:if (tf(map[a->py][a->px + 1][0]) == 1 && (a->px + 1) <= 10)//�E��
	{
		map[a->py][a->px + 1][1] = map[a->py][a->px][1];
		map[a->py][a->px][1] = 0;
		a->px += 1;
		break;
	}
	case 4:if (tf(map[a->py - 1][a->px][0]) == 1 && (a->py - 1) >= 1)//���
	{
		map[a->py - 1][a->px][1] = map[a->py][a->px][1];
		map[a->py][a->px][1] = 0;
		a->py -= 1;
		break;
	}
	}
}