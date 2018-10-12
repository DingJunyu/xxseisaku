#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#define d3 3
#define d4 4
#define d6 6
#define d8 8
#define d10 10
#define d12 12
#define d20 20

/*�z��map*/
/*�����W�A�����W�A�w*/
/*�w���F0�A�n�`�ۑ��@1�A�z���_�[�@�Q�A���[�g�T���Ƃ��̃f�[�^�ۑ��@3�Aconsole�A�o�p*/
int map[8 + 2][10 + 2][4];
/*�z��way*/
/*���[�g�ۑ�*/
int way[65][2];
/*�z��targetx,targety*/
/*�ڕW�ʒu���W�ۑ�*/
int targetx[5], targety[5];
/*�z��muchx,muchy*/
/*�ꎞ�d�ݕۑ��p*/
int muchx[65];
int muchy[65];
/*checker*/
/*���[�g��������Ȃ��ꍇ�֐����I��点��*/
int checker;

struct unitdata
{
	char name[20];//���O�ۑ�
	int att;//�U����
	int hp;
	int maxhp;//�ő�HP
	int magicdef;
	int phdef;
	int range;//�܂��g���ĂȂ��A�@�\��atttype�ƈꏏ
	int move;//�ړ���
	int atttype;//1�͋ߋ��������@2�͉�����(����)�@3�͉�� 4�͉��(���@) 5�͉�����(���@)
	int recovery;//�񕜗�
	int skill; //�������Ă�o�b�t1:�h��Ԑ� 2.�h��A�b�v 3.�U���A�b�v
	int px; //�����W
	int py; //�����W
	int type;//�E��
};


/*shortfuncionts.c*/
/*�Z���ėp�֐�*/
/*ra�֐�*/
/*�T�C�R���֐��ADND�K���Ɋ�Â���*/
/*�A��:*/
/*�T�C�R���̐�*/
/*�T�C�R���̖ʐ�*/

/*�Ԃ��l*/
/*�����_������*/
int ra(int, int);

/*reset �֐�*/
/*�z��̃}�b�v�z�u�w���폜*/
void reset();

/*checkfield�֐�*/
/*���̍��W�̓}�b�v�ӂ𒴂��邩�ǂ���*/
/*�A��:*/
/*x,y:���W*/

/*�Ԃ��l:*/
/*1:�^*/
/*0:�U*/
int checkfield(int x, int y);

/*teamcheck�֐�*/
/*�G�����������f*/
/*�A��:*/
/*x,y:��̒P�ʂ̔ԍ�*/

/*�Ԃ��l*/
/*0:�֌W�Ȃ�*/
/*1:�G*/
/*2:����*/
int teamcheck(int x, int y);

/*readmap�֐�*/
/*��������͂��āA�Ή��}�b�v��ǂݍ���*/
/*�A��:*/
/*x:�}�b�v�ԍ�*/
void readmap(int x);

/*typeret�֐�*/
/*�U����ނɂ���čU���ތ^��Ԃ�*/
/*�A��:*/
/*x�͍U�����*/

/*�Ԃ��l*/
/*0:�͈͊O*/
/*1:���@*/
/*2:�͕���*/
int typeret(int x);

/*scanwild�֐�*/
/*�͈̓`�F�b�N������͊֐�*/
/*�A��:*/
/**x:�^�[�Q�b�g�ϐ��̃A�h���X*/
/*a:����*/
/*b:���*/
void scanfwild(int *x, int a, int b);

/*hprand�֐�*/
/*�����_�������𐶐����鎞�����ɑ��̕ϐ��ɓ����������p*/
/*�A��:*/
/*x,y:�͖ڕW�ϐ�*/
/*a:�T�C�R����*/
/*b:�T�C�R���ʐ�*/
void hprand(int *x, int *y, int a, int b);

/*resetunit�֐�*/
/*���j�b�g�f�[�^��������*/
/*�A��:*/
/*x:�ڕW�P�ʂ̍\���̂̃A�h���X*/
void resetunit(void *x);

/*roundshow�֐�*/
/*�A�o�̎��A���E���h�ƃ��j�b�g�ԍ����*/
/*�A��:*/
/*���j�b�g�ԍ�*/
/*�J�����g�ԍ�*/
void roundshow(int, int);


/*ai.c*/
/*�p�\�R�����s���p�R�[�h*/

/*myturn�֐�*/
/*�p�\�R��������������*/
/*���͒l:*/
/*r:���Ԓl()*/
/*me:�`�[��B�̃��j�b�g�P�̃A�h���X*/
/*target:�`�[��A�̃��j�b�g�P�̃A�h���X*/
/*res:����̎c��P�ʐ�*/

/*�Ԃ��l*/
/*2:���̃��j�b�g�͂����s���s�\*/
/*1:����`�[�����S��*/
/*0:����ɏI���*/
int myturn(int *r, void *me, void *target, int *res);

/*findmyway�֐�*/
/*���[�g�T���p�֐��A��ԋ߂��G�̌������Ĉړ��\�R�}��T��*/
/*���͒l:*/
/*x,y:���݂̍��W*/
/*mynum:���j�b�g�̔ԍ�*/
/*ct:�֐��̑w��*/
/*mount:�s����ꏊ�̐�*/

/*�Ԃ��l*/
/*1:���ʂ�T���܂���*/
/*0:���ʂ������Ă܂���ł���*/
int findmyway(int startposx, int startposy, int thenumber, int ctis1, int mountis1);

/*resetmyway�֐�*/
/*���[�g�ۑ��p�̔z����N���A*/
void resetmyway();

/*showmethemap*/
/*�f�o�b�O�p�֐�*/
/*���[�g�T���̏�Ԃ�\��*/
void showmethemap();


/*randommapbuilder.c*/
/*�����_���}�b�v�𐶂�*/

/*randommap�֐�*/
/*�����_���}�b�v�𐶂�*/
void randommap();

/*findtheposition*/
/*�����_���}�b�v���ގ��A�����ʒu�𐶐�����*/
/*�A��:*/
/**x:�`�[��A�̃��j�b�g1�̃A�h���X*/
/**y:�`�[��B�̃��j�b�g2�̃A�h���X*/
void findtheposition(void *x, void *y);


/*displayoutput.c*/
/*��ʗA�o�ւ���֐��W*/

/*show�֐�*/
/*�}�b�v��`���֐�*/
void show(void *x, void *y);






/*showmove�֐�*/
/*�ړ��ł���ʒu�ɐ�����t����*/
int showmove(void *x);//�ړ��ł���Ƃ����\��

void randomdata(void *x, int y, int z, int p);//�E�Ƃɂ��f�[�^���쐬���� //�E�Ƃ̃f�[�^�͂����ł�

void movem(void *x, int y);//�ړ��֐�
void attshow(void *x,  int *tx, int *ty,int *tc);//�U���^�[�Q�b�g��\��
int attack(void *x, void *y,  int *tx, int *ty, int cout);//�U���֐�




void healshow(void *x,  int *tx, int *ty, int *tc);//���Ã^�[�Q�b�g��\��
void heal(void *x, void *y,  int *tx, int *ty, int cout);//���Ê֐�

void defendmode(int *x); //�h���ԂɈڍs
void title(); //�Q�[���̃^�C�g��
int round(int *r, void *x, void *y,  int *res);//����s���֐�

void kansushow( void *x, void *y, int i);//�֐��̒���show������ɓ����Ȃ��Ƃ��g�����f�t��show�֐�
void choosemap( void *x, void *y);//�L���[�y�����[�h�̃}�b�v�I��



int pcattack(void *x, void *y, int *tx, int *ty, int cout);
void unitdesign(void *x);