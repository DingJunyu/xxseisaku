#include<stdio.h>
#include"game.h"
int main()
{
	int i, j;
	int map[8+1][10+1][3];//[0]�͒n�`��ۑ�[1]�Ƀz���_�[[2]��ai�����[�g�T���p
	int mapr[8 + 1][10 + 1];

	FILE *mpr;
	mpr = fopen("map.txt", "r");

	for(i=0;i<=8;i++)
		for (j = 0; j <= 10; j++)
		{
			fscanf(mpr, "%d", mapr[i][j]);
		}

	for (i = 0; i <= 8; i++)
		for (j = 0; j <= 10; j++)
		{
			map[i][j][1] = map[i][j][2] = 0;
			map[i][j][0] = mapr[i][j];
		}
	show(&map);
}