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

/*配列map*/
/*ｘ座標、ｙ座標、層*/
/*層数：0、地形保存　1、ホルダー　２、ルート探すときのデータ保存　3、console輸出用*/
int map[8 + 2][10 + 2][4];
/*配列way*/
/*ルート保存*/
int way[65][2];
/*配列targetx,targety*/
/*目標位置座標保存*/
int targetx[5], targety[5];
/*配列muchx,muchy*/
/*一時重み保存用*/
int muchx[65];
int muchy[65];
/*checker*/
/*ルートを見つからない場合関数を終わらせる*/
int checker;

struct unitdata
{
	char name[20];//名前保存
	int att;//攻撃力
	int hp;
	int maxhp;//最大HP
	int magicdef;
	int phdef;
	int range;//まだ使ってない、機能はatttypeと一緒
	int move;//移動力
	int atttype;//1は近距離直線　2は遠距離(物理)　3は回り 4は回り(魔法) 5は遠距離(魔法)
	int recovery;//回復力
	int skill; //今持ってるバッフ1:防御態勢 2.防御アップ 3.攻撃アップ
	int px; //ｘ座標
	int py; //ｙ座標
	int type;//職種
};


/*shortfuncionts.c*/
/*短い汎用関数*/
/*ra関数*/
/*サイコロ関数、DND規則に基づいた*/
/*輸入:*/
/*サイコロの数*/
/*サイコロの面数*/

/*返す値*/
/*ランダム数字*/
int ra(int, int);

/*reset 関数*/
/*配列のマップ配置層を削除*/
void reset();

/*checkfield関数*/
/*今の座標はマップ辺を超えるかどうか*/
/*輸入:*/
/*x,y:座標*/

/*返す値:*/
/*1:真*/
/*0:偽*/
int checkfield(int x, int y);

/*teamcheck関数*/
/*敵か味方か判断*/
/*輸入:*/
/*x,y:二つの単位の番号*/

/*返す値*/
/*0:関係ない*/
/*1:敵*/
/*2:味方*/
int teamcheck(int x, int y);

/*readmap関数*/
/*数字を入力して、対応マップを読み込む*/
/*輸入:*/
/*x:マップ番号*/
void readmap(int x);

/*typeret関数*/
/*攻撃種類によって攻撃類型を返す*/
/*輸入:*/
/*xは攻撃種類*/

/*返す値*/
/*0:範囲外*/
/*1:魔法*/
/*2:は物理*/
int typeret(int x);

/*scanwild関数*/
/*範囲チェック入り入力関数*/
/*輸入:*/
/**x:ターゲット変数のアドレス*/
/*a:下限*/
/*b:上限*/
void scanfwild(int *x, int a, int b);

/*hprand関数*/
/*ランダム数字を生成する時同時に他の変数に導入したい用*/
/*輸入:*/
/*x,y:は目標変数*/
/*a:サイコロ数*/
/*b:サイコロ面数*/
void hprand(int *x, int *y, int a, int b);

/*resetunit関数*/
/*ユニットデータを初期化*/
/*輸入:*/
/*x:目標単位の構造体のアドレス*/
void resetunit(void *x);

/*roundshow関数*/
/*輸出の時、ラウンドとユニット番号を提示*/
/*輸入:*/
/*ユニット番号*/
/*カレント番号*/
void roundshow(int, int);


/*ai.c*/
/*パソコン側行動用コード*/

/*myturn関数*/
/*パソコン側動きを実現*/
/*入力値:*/
/*r:順番値()*/
/*me:チームBのユニット１のアドレス*/
/*target:チームAのユニット１のアドレス*/
/*res:相手の残る単位数*/

/*返す値*/
/*2:このユニットはもう行動不能*/
/*1:相手チームが全滅*/
/*0:正常に終わり*/
int myturn(int *r, void *me, void *target, int *res);

/*findmyway関数*/
/*ルート探す用関数、一番近い敵の向かって移動可能コマを探す*/
/*入力値:*/
/*x,y:現在の座標*/
/*mynum:ユニットの番号*/
/*ct:関数の層数*/
/*mount:行ける場所の数*/

/*返す値*/
/*1:結果を探しました*/
/*0:結果を見つけてませんでした*/
int findmyway(int startposx, int startposy, int thenumber, int ctis1, int mountis1);

/*resetmyway関数*/
/*ルート保存用の配列をクリア*/
void resetmyway();

/*showmethemap*/
/*デバッグ用関数*/
/*ルート探すの状態を表す*/
void showmethemap();


/*randommapbuilder.c*/
/*ランダムマップを生む*/

/*randommap関数*/
/*ランダムマップを生む*/
void randommap();

/*findtheposition*/
/*ランダムマップ生む時、初期位置を生成する*/
/*輸入:*/
/**x:チームAのユニット1のアドレス*/
/**y:チームBのユニット2のアドレス*/
void findtheposition(void *x, void *y);


/*displayoutput.c*/
/*画面輸出関する関数集*/

/*show関数*/
/*マップを描く関数*/
void show(void *x, void *y);






/*showmove関数*/
/*移動できる位置に数字を付ける*/
int showmove(void *x);//移動できるところを表す

void randomdata(void *x, int y, int z, int p);//職業によるデータを作成する //職業のデータはここです

void movem(void *x, int y);//移動関数
void attshow(void *x,  int *tx, int *ty,int *tc);//攻撃ターゲットを表す
int attack(void *x, void *y,  int *tx, int *ty, int cout);//攻撃関数




void healshow(void *x,  int *tx, int *ty, int *tc);//治療ターゲットを表す
void heal(void *x, void *y,  int *tx, int *ty, int cout);//治療関数

void defendmode(int *x); //防御状態に移行
void title(); //ゲームのタイトル
int round(int *r, void *x, void *y,  int *res);//毎回行動関数

void kansushow( void *x, void *y, int i);//関数の中にshowが正常に動かないとき使う判断付きshow関数
void choosemap( void *x, void *y);//キャーペンモードのマップ選ぶ



int pcattack(void *x, void *y, int *tx, int *ty, int cout);
void unitdesign(void *x);