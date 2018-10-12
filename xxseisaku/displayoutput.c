#include"game.h"
void showdata(char a[],int x,int y);
/*show関数*/
/*マップを描く関数*/
/*xはAチームの1番,yはBチームの1番*/
void show(void *x,void *y)//マップを表す関数ーーー基本バッジョン
{
	struct unitdata *a; //ホルダー 1 2 3 4 対応
	struct unitdata *b; //ホルダー 5 6 7 8対応

	a = (struct unitdata*)x;
	b = (struct unitdata*)y;


	int i, j;
	int cou = 0;

	/*画面をクリア*/
	system("cls");
	printf(" ");
	for (i = 1; i <= 10; ++i)
		printf("| %02d ", i);
	printf("|\n");
	for (i = 1; i <= 8; ++i)
	{
		printf(" ");
		for (j = 1; j <= 26; ++j)
		{
			printf("─");
		}
		
		printf("\n%d|",i);
		for (j = 1; j <= 10; ++j)
		{
			switch (map[i][j][0])
			{
			case 0:printf("  "); break;
			case 1:printf("山"); break;
			case 2:printf("川"); break;
			case 3:printf("屋"); break;
			case 4:printf("壁"); break;
			case 5:printf("橋"); break;
			case 6:printf("森"); break;
			}
			switch (map[i][j][1])
			{
			case 1:printf("①"); break;
			case 2:printf("②"); break;
			case 3:printf("③"); break;
			case 4:printf("④"); break;
			case 5:printf("壱"); break;
			case 6:printf("弐"); break;
			case 7:printf("参"); break;
			case 8:printf("四"); break;
			}
			switch(map[i][j][3])
			{
			case 0:if (map[i][j][1] == 0) printf("  "); break;
			case 1:printf(" 1"); break;
			case 2:printf(" 2"); break;
			case 3:printf(" 3"); break;
			case 4:printf(" 4"); break;
			}
			printf("|");
		}
	
		if (cou <= 3)
		{
			printf("  teamA%d:", cou + 1);
			showdata((a + cou)->name, (a + cou)->hp, (a + cou)->maxhp);
		}
		if (cou > 3)
		{
			printf("  teamB%d:", cou -3);
			showdata((b + (cou - 4))->name, (b + (cou - 4))->hp, (b + (cou - 4))->maxhp);
		}
		++cou;
		printf("\n");
	}
	printf(" ");
	for (j = 1; j <= 26; ++j)
	{
		printf("─");
	}
	printf("\n");
	return;
}

/*showdata関数*/
/*ユニットの名前、HPを表示*/
void showdata(char a[], int x, int y)
{
	printf("%8s",a);
	printf(" HP %2d/%2d",x,y);
	return;
}

/*title関数*/
/*タイトル描く関数*/
void title()
{
	system("cls");
	int i;
	printf(" \n　　　");
	for (i = 1; i <= 21; ++i)
		printf("＃");
	printf("\n");
	printf("　　　＃＃＃＃　 　   RPGテスター     　＃＃＃＃\n");
	printf("　　　＃＃＃＃　      version 5.2 　    ＃＃＃＃\n　　　");
	for (i = 1; i <= 21; ++i)
		printf("＃");
	printf("\n");
	printf(" \n");
}


/*kansushow関数*/
/*順位を正しいように表示する関数*/
void kansushow(void *x, void *y, int i)
{
	if (i > 4)
		show(x, y);
	else
		show(y, x);
}

/*choosemap関数*/
/*マップを選ぶ関数(デザインしたもの)*/
void choosemap(void *x, void *y)
{
	int i;
	int inpu1;
	char dataname[100];

	FILE *up;

	struct unitdata *a; //ホルダー 1 2 3 4 対応
	struct unitdata *b; //ホルダー 5 6 7 8対応

	a = (struct unitdata*)x;
	b = (struct unitdata*)y;

	while (1)//タイトルとマップ選択
	{
		printf("   ・マップの番号を選んでください(1~6):");
		scanfwild(&inpu1, 1, 6);
		reset(); //マップを全部クリア
		readmap(inpu1);
		sprintf_s(dataname, 100, ".//mapdata//unitpos%d.txt", inpu1);
		fopen_s(&up, dataname, "r");
		for (i = 0; i <= 3; ++i)
		{
			fscanf_s(up, "%d %d", &(a + i)->px, &(a + i)->py);
			fscanf_s(up, "%d", &map[(a + i)->py][(a + i)->px][1]);
		}
		for (i = 0; i <= 3; ++i)
		{
			fscanf_s(up, "%d %d", &(b + i)->px, &(b + i)->py);
			fscanf_s(up, "%d", &map[(b + i)->py][(b + i)->px][1]);
		}
		fclose(up);
		printf("                                                                loading...");
		show(x, y);
		printf("--------------------マップ%2d--------------------\n", inpu1);
		printf("このマップで決めるか?YES--->1NO--->1以外:");
		scanf_s("%d", &inpu1);
		if (inpu1 == 1)
			return;
	}
}