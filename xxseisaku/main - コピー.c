#include"game.h"
//�w�b�h�t�@�C���Ȃǂƍ\���̂̐錾��game.h�ɂ���
//attack.c�͍U���֘A�֐�
//round.c�͖��^�[���s���֐�
//shortones.c�͒Z���֐�
//heal�͎��Ão�b�t�֐�
//showmap�͂��ׂĂ̗A�o�֘A
//moeve�͈ړ��֘A
//randomdata�̓��j�b�g�f�[�^�𐶐��p�֐�

int main()
{
	int i,j=1;//�e�X�g�p�ϐ�
	int tarx[5] = {0};//a[][1]--->x���Wa[][2]---->y���W
	int tary[5] = { 0 };
	int tarc = 0;//�I�ׂ�^�[�Q�b�g�̐�
	int inpu1,inpu2=0;
	int resal=4, resen=4;//�����c��l���@�G�c��l��
	int coun=1;
	char dataname[100];

	FILE *up;

	struct unitdata allies[10]; //�z���_�[ 1 2 3 4 �Ή�
	struct unitdata enemy[10]; //�z���_�[ 5 6 7 8�Ή�

	int map[8+1][10+1][4];//[0]�͒n�`��ۑ�   [1]�̓z���_�[   [2]��ai�����[�g�T���p   [3]�͗A�o�p(�I��)(1-�� 2-�� 3-�E 4-�� 5-�A�o���Ȃ�)

	title();
	
	while (1)
	{
		for (i = 1; i <= 4; i++)//���j�b�g�̃f�[�^������
		{
			resetunit(&allies[i]);
			resetunit(&enemy[i]);
		}

		while (1)//�^�C�g���ƃ}�b�v�I��
		{
			printf("   �E�}�b�v�̔ԍ���I��ł�������(1~6):");
			scanfwild(&inpu1, 1, 6);
			reset(map); //�}�b�v��S���N���A
			readmap(map, inpu1);
			sprintf_s(dataname, 100, ".//mapdata//unitpos%d.txt", inpu1);
			fopen_s(&up, dataname, "r");
			for (i = 1; i <= 4; i++)
			{
				fscanf_s(up, "%d %d", &allies[i].px, &allies[i].py);
				fscanf_s(up, "%d", &map[allies[i].py][allies[i].px][1]);
			}
			for (i = 1; i <= 4; i++)
			{
				fscanf_s(up, "%d %d", &enemy[i].px, &enemy[i].py);
				fscanf_s(up, "%d", &map[enemy[i].py][enemy[i].px][1]);
			}
			fclose(up);
			show(map, &allies[1], &enemy[1]);
			printf("--------------------�}�b�v%2d--------------------\n",inpu1);
			printf("���̃}�b�v�Ō��߂邩?YES--->1NO--->1�ȊO:");
			scanf_s("%d", &inpu1);
			if (inpu1 == 1)
				break;
		}
		//�c��l�������Z�b�g
		resal = 4; resen = 4;

		//�`�[��A��B�̃��j�b�g�^�C�v��I��
		for (i = 1; i <= 4; i++)
		{
			show(map, &allies[1], &enemy[1]);
			randomdata(&allies[i], i,1);
			show(map, &allies[1], &enemy[1]);
			randomdata(&enemy[i], i, 2);
		}

		
		while (resal > 0 && resen > 0)
		{
			printf("-----------------------���E���h %d-----------------------", coun);
			getchar();
			i = 1;
			//�`�[��ab�̃R�����g�͓���
			while (i <= 4)
			{
				if (round(&i, &allies[1], &enemy[1], map, &resen) == 1)
					break;
				if (round(&i, &enemy[1], &allies[1], map, &resal) == 1)
					break;
				i++;
			}
			coun++;
		}

		show(map, &allies[1], &enemy[1]);
		if (resen == 0)
			printf("�v���[���[�P�̏���\n");
		if (resal == 0)
			printf("�v���[���[�Q�̏���\n");
		printf("�����邩�H0->YES");
		scanf_s("%d", &inpu1);
		if (inpu1 != 0)
			break;
	}
	return 0;
}