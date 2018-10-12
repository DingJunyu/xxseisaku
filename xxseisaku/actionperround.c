#include"game.h"

/*round�֐�*/
/*r:�Y�����j�b�g�̔ԍ�,x:x���W,y:y���W,res:�c�������j�b�g��*/
/*return�l: 2:�Y���^�[�Q�b�g�͂������� 1:�`�[���͂����S�� 0:�Ȃ�ł��Ȃ�*/
int round(int *r,void *x,void *y,int *res)
{
	/*�^�[�Q�b�g�f�[�^�ۑ��p�ϐ�tarx,tary,tarc*/
	int tary[5];
	int tarx[5];
	int tarc=0;
	/*�ړ��񐔓��v�ϐ�movecount*/
	int movecount;
	/*���͗p�ϐ�inpu1,inpu2*/
	int inpu1=0,inpu2=0;
	/*�J��Ԃ��p�ϐ�j,k*/
	int j, k;
	/*�^�[�Q�b�g�ԍ��C���p�ϐ�ba,sa*/
	/*�}�b�v�̍��W�ɂ���āA�e�`�[���̃��j�b�g�ԍ��ɕς��*/
	int ba, sa;
	/*�s�����ʏC���p�ϐ�*/
	int mark = 0;
	int canyoumove;

	struct unitdata *a, *b;

	a = (struct unitdata*)x;
	b = (struct unitdata*)y;

	if (*res <= 0)
		return 1;

	/*A�`�[���̃^�[��*/
	/*r�̒l������B�`�[���̃��j�b�g�ɂȂ�*/
	if (*r <= 4)
	{
		j = *r-1;
		*r += 4;
		mark = 1;
	}
	/*B�`�[���̃^�[�^��*/
	/*���̒l��A�`�[���͈͓̔��ɖ߂�*/
	if (*r > 4 && mark == 0)
	{
		j = *r - 5;
		*r -= 4;
	}

	/*�^�[�Q�b�g�͎��񂾏ꍇ�̓^�[�����X�L�b�v*/
	if ((a+j)->hp <= 0)
		return 2;

	/*��ʂ�`��*/
	kansushow(a,b,*r);
	roundshow(*r, j);
	/*�s���ԍ������*/
	printf("�s����I��ł�������(1.�ړ� 2.�U�� 3.��/�X�L�[�� 4.�h��Ԑ� 0,�I���)�F");
	scanfwild(&inpu1, 0, 4);

	movecount = 0;
	/*�ړ�*/
	while (inpu1 == 1)
	{
		++movecount;
		canyoumove=showmove(a+j);
		kansushow(a,b,*r);
		roundshow(*r, j);
		movem(a+j, canyoumove);
		kansushow(a,b,*r);
		roundshow(*r, j);
		/*���������Ĉړ����ł��Ȃ��ꍇ*/
		if ((a+j)->move == 1 || movecount == (a+j)->move || map[(a+j)->py][(a+j)->px][0] == 6||canyoumove==0)
		{
			printf("�s����I��ł�������(1.�U�� 2.��/�X�L�[�� 3.�h��Ԑ� 0,�I���)�F");
			scanfwild(&inpu2, 0, 3);
			inpu1 = 0;
			break;
		}
		/*�܂�������ꍇ*/
		else
		{
			printf("�s����I��ł�������(1.�ړ� 2.�U�� 3.��/�X�L�[�� 4.�h��Ԑ� 0,�I���)�F");
			scanfwild(&inpu1, 0, 4);
			if (inpu1 != 1)
				break;
		}
	}
	
	/*�U��*/
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
				printf("%d��:X:%d Y:%d %s %d/%d\n", k, tarx[k], tary[k], (b + sa)->name, (b + sa)->hp, (b + sa)->maxhp);
			}
			*res -= attack(a+j, b, &tarx[1], &tary[1], tarc);
			if (*res <= 0)//�G���S�����񂾂炨���
				return 1;
		}
		if (tarc <= 0)
		{
			printf("�U���ł���^�[�Q�b�g�����܂���B\n");
			printf("2.��/�X�L�[�� 3.�h��Ԑ� 0,�I���B\n");
			scanf_s("%d", &inpu2);
		}
		/*�^�[�Q�b�g�����Z�b�g*/
		tarc = 0; tarx[1] = 0; tary[1] = 0;
	}

	/*����*/
	if (inpu1 == 3 || inpu2 == 2)
	{
		healshow(a+j, &tarx[1], &tary[1], &tarc);
		kansushow(a,b,*r);
		if (tarc != 0)
		{
			roundshow(*r, j);
			printf("1��:X:%d Y:%d %s %d/%d\n", tarx[1], tary[1], (a + j)->name, (a + j)->hp, (a + j)->maxhp);
			for (k = 2; k <= tarc; ++k)
			{
				if (map[tary[k]][tarx[k]][1] > 4)
					ba = map[tary[k]][tarx[k]][1] - 4;
				else
					ba = map[tary[k]][tarx[k]][1] - 1;
				printf("%d��:X:%d Y:%d %s %d/%d\n", k, tarx[k], tary[k], (a + ba)->name, (a + ba)->hp, (a + ba)->maxhp);
			}
			heal(a+j, a, &tarx[1], &tary[1], tarc);
		}
		/*�^�[�Q�b�g�����Z�b�g*/
		tarc = 0; tarx[1] = 0; tary[1] = 0;
	}

	(a+j)->skill = 0;

	/*�o�b�t*/
	if (inpu1 == 4 || inpu2 == 3)
	{
		defendmode(&(a+j)->skill);
		printf("%s�͖h��Ԑ��Ɉڍs���ꂽ\n", (a+j)->name);
	}

	printf("�^�[���I��");
	rewind(stdin);
	getchar();

	return 0;
}