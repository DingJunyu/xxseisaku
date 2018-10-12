#include"game.h"
#define magic "���@�g��"//���@�_���[�W���o�����A�ߋ����Ɖ��������ނ�����//�����_����//�ߋ����̂ق��̑̂�����v		
#define archer "�ˎ�" //��̖ڂ��z���čU�����ł���
#define warrior "��m" //
#define priest "�q�t" //�񕜖�
#define lancer "���g��" //�ΐ��U�����ł����m(hp�͐�m���Ⴂ���A�U���͂�������)
#define paladin "�R�m"//�h��͂�����
#define jongleur "��V���l"//buff
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
	pt->atttype = 1;//1->�l����1�R�}���� 2->�������P�R�}�A�l�����Q�R�}���� 3->�������P�R�}���� 4->�������P�R�}���@ 5->�������P�R�}�A�l�����Q�R�}���@
	pt->recovery = 2;
	pt->skill = 0;

//	system("cls");

	if (p == 1)
	{
		printf("1�͖��@�g��(���������@�U���^�C�v)\n");
		printf("2�͎ˎ�(�����������U���^�C�v)\n");
		printf("3�͐�m(�ߋ��������U���^�C�v)\n");
		printf("4�͖q�t(�ߋ����ΐ��U�����ł��閂�@�U���^�C�v�AHP�񕜗ʂ�����)\n");
		printf("5�͑��g��(�ߋ����ΐ��U�����ł��镨���U���^�C�v)\n");
		printf("6�͋R�m(�ߋ��������U���^�C�v�A�h��͂�����)\n");
		printf("7�͋�V���l(�����X�L�[������)\n");
		printf("8�̓��j�b�g�����\n");
		if (z == 1)
			printf("�`�[��A��");
		if (z == 2)
			printf("�`�[��B��");
		printf("���j�b�g%d�̃^�C�v��I��ł�������:", y);
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
	pt->atttype = 1;//1->�l����1�R�}���� 2->�������P�R�}�A�l�����Q�R�}���� 3->�������P�R�}���� 4->�������P�R�}���@ 5->�������P�R�}�A�l�����Q�R�}���@
	pt->recovery = 2;
	pt->skill = 0;

	count = 8;

	system("cls");
	printf("���j�b�g�̖��O����͂��Ă��������B(4�����ȓ�)");
	scanf_s("%s", &pt->name, 20);
	printf("���j�b�g�̍U���^�C�v��I��ł��������B\n�E������1�A���@�͂Q�B");
	scanfwild(&inpu1, 1, 2);
	if (inpu1 == 1)
	{
		printf("�U���͈͂�I��ł��������B\n�l�����P�R�}��1�A�������P�R�}��2�A�l����2�R�}��3�B");
		scanfwild(&inpu2, 1, 3);
		if (inpu2 == 1)pt->atttype = 1;
		if (inpu2 == 2)pt->atttype = 3;
		if (inpu2 == 3)pt->atttype = 2;
	}
	if (inpu1 == 2)
	{
		printf("�U���͈͂�I��ł��������B\n�������P�R�}��1�A�l����2�R�}��2�B");
		scanfwild(&inpu2, 1, 2);
		if (inpu2 == 1)pt->atttype = 4;
		if (inpu2 == 2)pt->atttype = 5;
	}
	printf("�s���͂�I��ł��������B1��/�^�[����1,2��/�^�[����2�B(2�̓`�P�b�g2����)");
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
		printf("�U���͂��A�b�v�����1\n");
		printf("H    P���A�b�v�����2\n");
		printf("�����h��͂��A�b�v�����3\n");
		printf("���@�h��͂��A�b�v�����4\n");
		printf("�񕜗͂��A�b�v�����5\n");
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
	printf("���O:%s\n", pt->name);
	printf("H  P:%d\n", pt->maxhp);
	if (typeret(pt->atttype) == 1);
	printf("�����U��\n");
	printf("�U����:%d\n", pt->att);
	printf("�����h���:%d\n", pt->phdef);
	printf("���@�h���:%d\n", pt->magicdef);
	printf("��  ��  ��:%d\n", pt->recovery);
	printf("�c�����`�P�b�g:%d\n \n", cout);
}