#include"game.h"

int main()
{
	/*�e�X�g�A�J��Ԃ��p�ϐ�i,j*/
	int i,j=1;
	/*���͗p�ϐ�inpu1,inpu2*/
	int inpu1,inpu2=0;
	/*�`�[��A�c��l��resal,�`�[��B�c��l��resen*/
	int resal=4, resen=4;
	/*���E���h�J�E���^�[*/
	int coun=1;

	/*�\���̂��g���ă`�[��A�ƃ`�[��B��錾*/
	/*�z���_�[�Ή��F*/
	/*allies 1~4: �z���_�[ 1~4*/
	/*enemy 1~4:�z���_�[ 5~8*/
	struct unitdata allies[10];
	struct unitdata enemy[10];


	while (1)
	{
		/*�S���j�b�g��������*/
		for (i = 1; i <= 4; i++)
		{
			resetunit(&allies[i]);
			resetunit(&enemy[i]);
		}

		/*�}�C�����j���[��`��*/
		title();
		printf("  �E1.�����_���}�b�v\n  �E2.�L���[�y���}�b�v\n  �E3.�I���\n  ");
		scanfwild(&inpu1, 1, 3);

		if (inpu1 == 3)
			break;

		/*�����_���}�b�v�𐶐��A����*/
		while (inpu1 == 1)
		{
			printf("                                                                loading...");
			randommap();
			findtheposition(&allies[1], &enemy[1]);
			show(&allies[1], &enemy[1]);

			printf("���̃}�b�v�Ō��߂܂���?YES--->1NO--->1�ȊO");
			scanf_s("%d", &inpu2);
			if (inpu2 == 1)
				break;
		}

		if (inpu1 == 2)
		choosemap(&allies[1], &enemy[1]);

		printf("  �E1.�ΐ탂�[�h\n  �E2.�p�\�R���Ƃ̑ΐ�\n");
		scanfwild(&inpu1, 1, 2);
		/*���`�[���c��l�������Z�b�g*/
		resal = 4; resen = 4;

		/*���j�b�g��I��*/
		for (i = 1; i <= 4; i++)
		{
			show(&allies[1], &enemy[1]);
			randomdata(&allies[i], i,1, 1);
			if(inpu1==1)
			show(&allies[1], &enemy[1]);
			randomdata(&enemy[i], i, 2, inpu1);
		}

		
		/*PVP���E���h����*/
		while (resal > 0 && resen > 0 && inpu1 == 1)
		{
			printf("-----------------------���E���h %d-----------------------", coun);
			getchar();
			i = 1;
			while (i <= 4)
			{
				if (round(&i, &allies[1], &enemy[1], &resen) == 1)
					break;
				if (round(&i, &enemy[1], &allies[1], &resal) == 1)
					break;
				i++;
			}
			coun++;
		}

		/*PVE���E���h����*/
		while (resal > 0 && resen > 0 && inpu1 == 2)
		{
			printf("-----------------------���E���h %d-----------------------", coun);
			getchar();
			i = 1;
			while (i <= 4)
			{
				if (round(&i, &allies[1], &enemy[1], &resen) == 1)
					break;
				if (myturn(&i, &enemy[1], &allies[1], &resal) == 1)
					break;
				i++;
			}
			coun++;
		}

		/*�Ō�̃}�b�v��Ԃ�\��*/
		show(&allies[1], &enemy[1]);
		if (resen == 0)
			printf("�v���[���[�P�̏���\n");
		if (resal == 0)
			printf("�v���[���[�Q�̏���\n");

		system("pause");
	}
	return 0;
}
//1631 2018.07.09