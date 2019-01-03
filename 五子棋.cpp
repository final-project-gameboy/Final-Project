#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//棋盤初始化
//Chessboard=棋盤,ln=棋盤寬度
void init_Chessboard(char Chessboard[][7], int ln)
{
	if ((Chessboard != NULL) && (ln>0)){
		int i = 0, j = 0;
		for (i = 0; i<ln; ++i){
			for (j = 0; j<ln; ++j){
				Chessboard[i][j] = '\t';
			}
		}
	}
}


//顯示棋盤**************************************************************************************************
void show_Chessboard(char Chessboard[][7], int ln)
{
	assert((Chessboard != NULL) && (ln > 0));

	int i = 0, j = 0;
	for (i = 0; i<ln; ++i){
		putchar('\t');
		putchar(i + '0');
	}

	putchar('\n');
	putchar('\n');

	for (i = 0; i<ln; ++i){
		putchar(i + '0');
		for (j = 0; j<ln; ++j){
			if ('\t' == Chessboard[i][j]){
				putchar(Chessboard[i][j]);
			}
			else
			{
				putchar('\t');
				putchar(Chessboard[i][j]);
			}

		}
		putchar('\n');
		putchar('\n');
	}
}

//下棋子
//下棋成功return 1 沒成功return 0
int play_five(char Chessboard[][7], int ln, int x, int y, char ChessPieces)
{
	assert(Chessboard);

	if ((x<ln) && (y<ln) && (x >= 0) && (y >= 0)){
		if ('\t' == Chessboard[x][y]){

			Chessboard[x][y] = ChessPieces;
			return 1;  
		}
		else
		{
			return 0;
		}
	}
	return 0;
}

//判斷是否滿盤
//滿return 1 沒有return 0
int full_Chess(char Chessboard[][7], int ln)
{
	int i = 0, j = 0;
	for (i = 0; i<ln; ++i){
		for (j = 0; j<ln; ++j){
			if ('\t' == Chessboard[i][j]){
				return 0;  //未滿
			}
		}
	}

	return 1;//滿了

}


//判?是否連成五子且一樣
//Chessboard=棋盤,ln=棋盤寬度,(XS,YS)方向判斷起點座標,(dx,dy)方向增量
//有成功return 1，?有return 0
int judge_line(char Chessboard[][7], int ln, int XS, int YS, int dx, int dy)
{
	assert((Chessboard != NULL) && (ln > 0));

	if ((XS <ln) && (YS<ln)             //起?點座標在棋盤內
		&& (XS >= 0) && (YS >= 0)
		&& (dx != 0 || dy != 0))        //座標增量不同時為0
	{

		if (((XS + dx * 4) > ln) || ((XS + dx * 4)<0) || //判??點座標
			((YS + dy * 4)>ln) || ((YS + dy * 4) < 0) || //在棋盤外
			('\t' == Chessboard[XS][YS]))
		{
			return 0;  //不在棋盤?or起點?下棋子
		}


		else
		{
			for (int i = 1; i < 5; ++i){
				if (Chessboard[XS][YS] != Chessboard[XS + (dx * i)][YS + (dy * i)]){
					return 0;  //如果不是連續5個一樣的
				}
			}
			return 1;
		}
	}
	return 0;  //其他情?
}


//判斷函數
//Chessboard 棋盤，ln=棋盤寬度
//?了return 1，沒有 return 0
int judge(char Chessboard[][7], int ln)//ln=7
{
	assert((NULL != Chessboard) && (ln>0));

	int i = 0, j = 0;
	//縱向成五子連線判?*********************************************
	for (i = 0; i<(ln - 4); ++i){
		for (j = 0; j<ln; ++j){
			if (judge_line(Chessboard, ln, i, j, 1, 0)){
				return 1;
			}
		}
	}

	//?向成五子連線判?**********************************************
	for (i = 0; i<ln; ++i){
		for (j = 0; j<(ln - 4); ++j){
			if (judge_line(Chessboard, ln, i, j, 0, 1)){
				return 1;
			}
		}
	}

	//左上到右下成五子連線判?*****************************************
	for (i = 0; i<(ln - 4); ++i){
		for (j = 0; j<(ln - 4); ++j){
			if (judge_line(Chessboard, ln, i, j, 1, 1)){
				return 1;
			}
		}
	}

	//左下到右上成五子連線判?******************************************
	for (i = ln - 1; i>(ln - 4); --i){
		for (j = 0; j <(ln - 4); ++j){
			if (judge_line(Chessboard, ln, i, j, -1, 1)){
				return 1;
			}
		}
	}

	return 0;  //?有?
}

//主函?
int main()
{
	char CB[7][7];
	char nameA[50] = "玩家A";
	char nameB[50] = "玩家B";
	int x = -1, y = -1;

	//棋盤初始化**************************************************************************************************
	init_Chessboard(CB, 7);

	//設定玩家名子*************************************************************************************************
	printf("請輸入玩家A的名字:");
	scanf("%s", nameA);
	printf("請輸入玩家B的名字:");
	scanf("%s", nameB);

	//顯示棋盤*****************************************************************************************************
	show_Chessboard(CB, 7);

	while (1){
		//判斷棋盤是否滿了
		if (full_Chess(CB, 7)){
			puts("\n棋?已?，下次再?！");
			break; //跳出到最外層的while
		}


		//A下棋****************************************************************************************************
		while (1){
			printf("\n請玩家 %s 下子 @\n", nameA);
			printf("縱座標=");
			scanf("%d", &x);
			printf("橫座標=");
			scanf("%d", &y);

			if (play_five(CB, 7, x, y, '@')){  
				break;   
			}
			else
			{
				puts("下子失敗，請重新找新位置下子");
				continue;  //下子不成功，重新下子
			}
		}

		//顯示棋盤**************************************************************************************************
		show_Chessboard(CB, 7);

		//判斷玩家A是否勝利*****************************************************************************************
		if (judge(CB, 7)){
			printf("\n恭喜玩家 %s 成功取得勝利！！\n", nameA);
			getchar();
			getchar();
			break; //跳出到最外層的while
		}//gameover!!!

		//B下棋****************************************************************************************************
		while (1){
			printf("\n請玩家 %s 下子 O\n", nameB);
			printf("縱座標=");
			scanf("%d", &x);
			printf("橫座標=");
			scanf("%d", &y);

			if ((play_five(CB, 7, x, y, 'O'))){ 
				break;     
			}
			else
			{
				puts("下子失?，?重新?定位置下子");
				continue;  //下子不成功，重新下子
			}

		}

		//顯示棋盤*************************************************************************************************
		show_Chessboard(CB, 7);

		//判斷玩家B是否勝利****************************************************************************************
		if (judge(CB, 7)){
			printf("\n恭喜玩家 %s 成功取得胜利！！ \n", nameA);
			getchar();
			getchar();
			break; //跳出到最外層的while
		}//gameover!!!

	}

	return 0;

}
