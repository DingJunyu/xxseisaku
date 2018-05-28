#include<stdio.h>
void show(int arr[11][11][3])
{
	int i, j;
	printf(" ");
	for (i = 1; i <= 10; i++)
		printf("| %02d ", i);
	printf("|\n");
	for (i = 1; i <= 8; i++)
	{
		printf(" ");
		for (j = 1; j <= 26; j++)
		{
			printf("„Ÿ");
		}
		
		printf("\n%d|",i);
		for (j = 1; j <= 10; j++)
		{
			switch (arr[i][j][0])
			{
			case 0:printf("Œ´"); break;
			case 1:printf("ŽR"); break;
			case 2:printf("ì"); break;
			case 3:printf("‰®"); break;
			case 4:printf("•Ç"); break;
			case 5:printf("‹´"); break;
			}
			switch (arr[i][j][1])
			{
			case 0:printf("@"); break;
			case 1:printf("p1"); break;
			case 2:printf("e1"); break;
			}
			printf("|");
		}
		printf("    unit1 20/20");
		printf("\n");
	}
	printf(" ");
	for (j = 1; j <= 26; j++)
	{
		printf("„Ÿ");
	}
	printf("\n");
}