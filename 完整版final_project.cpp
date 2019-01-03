#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include <math.h>
#include<time.h>
#include <windows.h>
#include <assert.h>
#define true 1
#define false 0
void start(int *pPillar, int size);
void play(int *pPillar, int size);
void show(int *pPillar, int size);
void menusnake();
char conversion(int temp);
bool endflag(int *pPillar, int size);
int puzzle();
int password();
int snake();
int five();
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
void position(int xpos, int ypos) //移動游標至指定位置 
{

	COORD scrn;

	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);

	scrn.X = xpos; scrn.Y = ypos;

	SetConsoleCursorPosition(hOuput, scrn);
}



void showCursor(int visible)//編程的簡單但有用的隱藏光標源代碼。 
{

	CONSOLE_CURSOR_INFO ConCurInf;

	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	GetConsoleCursorInfo(hStdOut, &ConCurInf);

	ConCurInf.bVisible = visible;

	SetConsoleCursorInfo(hStdOut, &ConCurInf);

}



typedef struct
{

	int x;
	int y;

}Snake;



Snake sBody[1000]; //不超過最大陣列長度


//蛇的身體
void printSnake(int i)
{

	position(sBody[i].x, sBody[i].y);

	printf("⊙");

}


//牆壁
void GameWall()
{

	int i, j;

	for (i = 0; i<28; i++){
		for (j = 5; j<110; j++){
			if (i == 0 || i == 27 || j == 5 || j == 109){
				position(j, i);
				printf(".");
			}
		}
	}
}


//右方的提示顯示
void Information(int food, int speed)
{
	position(40, 28);
	printf("分數: %d", food * 5);
	position(50, 28);
	if (speed == 300) printf("速度: %3d (最低速)", 310 - speed);
	else if (speed == 10) printf("速度: %3d (最高速)", 310 - speed);
	else printf("速度: %3d              ", 310 - speed);
}


//身體的座標 
void setSite(int i, int site_x, int site_y)
{

	sBody[i].x = site_x;

	sBody[i].y = site_y;

}


//蛇的初始顯示位置  但不是出發的位置 
void setStartSite(){

	int i;

	sBody[0].x = sBody[1].x = sBody[2].x = sBody[3].x = sBody[4].x = 12;

	for (i = 0; i<5; i++) sBody[i].y = abs(5 - i);

}
int main()
{
	char choice1;


	do
	{
	for(int a=2;a<25;a++){
    position(25,a);printf("║");
	position(74,a);printf("║");
}
	position(25,1);
	printf("╔═══════════  ☆ ☆  遊 戲 BOY  ☆ ☆════════════╗");
	position(25,25);
	printf("╚════════════════════════════════════════════════╝");
	position(32, 5);
	printf("歡迎來到遊戲BOY");
	position(32, 6);
	printf("在這裡可以盡情的玩到懷念的古早味小遊戲");
	position(32, 8);
	printf("遊戲列表:");
	position(32, 9);
	printf("1.益智遊戲");
	position(32, 10);
	printf("2.終極密碼");
	position(32, 11);
	printf("3.貪食蛇");
	position(32, 12);
	printf("4.雙人對打五子棋");
	position(32, 13);
	printf("5.離開遊戲BOY");
	position(32, 15);
	printf("請選擇想要遊玩的遊戲:");
	scanf(" %c", &choice1);
	

		switch (choice1)
		{
		case '1':
			system("CLS");
			puzzle();
			break;
		case '2':
			system("CLS");
			printf("終極密碼");
			password();
			break;
		case '3':
			system("CLS");
			snake();
			break;
		case '4':
			system("CLS");
			five();
			break;
		case '5':
			break;
		}
	} while (choice1 != '5');
	position(32, 20);
	system("pause");
	position(32, 25);
	return 0;
}
int puzzle()
{
	int size = 8, Pillar[size];
	srand(time(NULL));
	start(Pillar, size);
	play(Pillar, size);
	printf("       YOU WIN!!\n\n");
	system("pause");
system("CLS");

}
void start(int *pPillar, int size)
{
	int i;
	for (i = 0; i<size; i++)
		pPillar[i] = rand() % 2;
	printf("使用鍵盤旁的九宮格1,2,3,4,6,7,8,9對應圖形\n當按下目標鍵時其附近兩顆鍵目標鍵將會1和0轉換\n遊戲目的是將圖形全部改成1就獲勝!\n");
	show(pPillar, size);
}
void play(int *pPillar, int size)
{
	char key;
	int i, temp;
	key = getch();  //*1=49(0),*2=50(1),*3=51(2),4=52(5),6=54(7),*7=55(6),8=56(5),9=57(3) 
	for (i = -1; i<2; i++)
	{
		if (key >= 49 && key <= 57 && key != 53) temp = key - '1';
		else break;
		temp = (temp == 3) ? 7 + i : (temp == 5) ? 3 + i : (temp == 7) ? 5 + i : (temp == 8) ? 4 + i : temp + i;
		pPillar[(temp<0) ? 7 : (temp>7) ? 0 : temp] = !pPillar[(temp<0) ? 7 : (temp>7) ? 0 : temp];
	}
	show(pPillar, size);
	if (endflag(pPillar, size) != 1)	play(pPillar, size);
}
void show(int *pPillar, int size)
{
	int i;
	position(8, 2);
	printf("\n\n\t%c　%c　%c\n", conversion(pPillar[6]), conversion(pPillar[5]), conversion(pPillar[4]));
	printf("\t%c　　 %c\n", conversion(pPillar[7]), conversion(pPillar[3]));
	printf("\t%c　%c　%c\n\n", conversion(pPillar[0]), conversion(pPillar[1]), conversion(pPillar[2]));
}
char conversion(int temp)
{
	if (temp == 1) return 'I';
	else return 'O';
}
bool endflag(int *pPillar, int size)
{
	int i, count = 0;
	for (i = 0; i<size; i++)
		(pPillar[i] == 1) ? count++ : 0;
	if (count == 8) return 1;
	else return 0;
}
int password()
{
	int seed, guess, lower = 1, higher = 100, frequency = 1;
	srand(time(NULL));
	do
	{
		seed = rand() % 101;
	} while (seed == 0);
	printf("Enter a number between %d~%d\n", lower, higher); scanf("%d", &guess);
	do
	{
		if (lower <guess && guess<seed)
		{
			lower = guess;
			printf("Enter anumer between %d~%d   frequency=%d\n", lower, higher, frequency); scanf("%d", &guess);
			frequency++;
		}
		else if (guess>seed && higher>guess)
		{
			higher = guess;
			printf("Enter anumer between %d~%d   frequency=%d\n", lower, higher, frequency); scanf("%d", &guess);
			frequency++;
		}
		else
		{
			printf("It's not between %d~%d\n", lower, higher); scanf("%d", &guess);
		}
	} while (seed != guess);
	printf("bingo!!\n");
system("pause");
system("CLS");
}
void menusnake(){
	position(25,1);
	printf("╔══════════════  << 貪吃蛇遊戲 >>  ══════════════╗");
	position(25,16);
	printf("╚════════════════════════════════════════════════╝");
	for(int a=2;a<16;a++){
    position(25,a);printf("║");
	position(74,a);printf("║");
}

	position(40,2);	printf("             ■■        ■");
	position(40, 3);printf("~~●)■    ■    ■    ■");
	position(40,4);	printf("       ■■        ■■");
	position(40, 5);
	printf("一個目標為5分");
	position(40, 7);
	printf("控制為上 下 左 右");
	position(40, 9);
	printf("Q鍵來增加速度");
	position(40, 10);
	printf("E鍵來減少速度");
	position(40, 12);
	printf("T鍵 暫停");
	position(40,14);
	system("pause");
	system("CLS");
}
int snake()
{
	int startBodyLenght = 5, startEatenFood = 0, bodyLenght, eatenFood;
	int FirstKey, SecondKey;
	int i, j, dead = false, isFoodEaten = false, vary = false;
	int direction = 2; // 方向向下 
	int snakeSpeed = 100;
	char requirements = 'y';
	Snake foodSite, coor, last;
	menusnake();
	srand(time(NULL));
	showCursor(0);//移除掉打字的光點 
	setStartSite();
	GameWall();
	bodyLenght = startBodyLenght;
	eatenFood = startEatenFood;
	coor.x = 12;
	coor.y = 4;
	direction = 2;
	isFoodEaten = false;
	dead = false;
	vary = false;
	snakeSpeed = 70;
	Information(startEatenFood, snakeSpeed);

	for (i = 0; i<bodyLenght; i++)

		printSnake(i);


	//按R開始 (因為跳出迴圈所以到下一步驟) 
	do{
		position(50, 10);
		printf("R鍵-開始");
		requirements = getch();
		position(50, 10);
		printf("             ");
	} while (requirements != 'r');



	while (!dead){

		//更新記分板
		Information(eatenFood, snakeSpeed);

		// 如果沒食物, 隨機算出一個食物的位置
		if (!isFoodEaten){

			foodSite.x = rand() % 49 * 2 + 6;
			foodSite.y = rand() % 25 + 2;

			isFoodEaten = true;

		}

		position(foodSite.x, foodSite.y);

		printf("╳");

		vary = false;


		// 鍵盤操作 
		if (kbhit()){

			FirstKey = getch();

			//224是方向鍵的extended key
			if (FirstKey == 224) {

				SecondKey = getch();

				if (SecondKey == 72 && direction != 2){
					coor.y--;
					direction = 1;
					vary = true;
				}
				if (SecondKey == 80 && direction != 1){
					coor.y++;

					direction = 2;
					vary = true;
				}
				if (SecondKey == 75 && direction != 4){
					coor.x -= 2;

					direction = 3;
					vary = true;
				}
				if (SecondKey == 77 && direction != 3){
					coor.x += 2;

					direction = 4;
					vary = true;
				}





			}

			//P鍵暫停 
			if (FirstKey == 't' || FirstKey == 'T'){

				do{

					position(50, 10);
					printf("暫停");

					requirements = getch();

					position(50, 10);
					printf("          ");

				} while (requirements != 't' && requirements != 'T');

			}
			//Q號增加速度 
			if (FirstKey == 'q' || FirstKey == 'Q'){

				if (snakeSpeed > 10) snakeSpeed -= 10;

				FirstKey = '\0';

			}
			//E號減少速度 
			if (FirstKey == 'e' || FirstKey == 'E'){

				if (snakeSpeed < 300) snakeSpeed += 10;

				FirstKey = '\0';

			}

		}
		else { // 沒有任何動作則順著現方向前進

			switch (direction){

			case 1: //上 

				coor.y--;

				direction = 1;

				break;

			case 2: //下 

				coor.y++;

				direction = 2;

				break;

			case 3: //左 

				coor.x -= 2;

				direction = 3;

				break;

			case 4: //右 

				coor.x += 2;

				direction = 4;

				break;

			}

			vary = true;

		}

		//碰到自己身體結束遊戲 
		for (i = 1; i<bodyLenght; i++){

			if (coor.x == sBody[i].x && coor.y == sBody[i].y)

				dead = true;
		}
		//蛇移動 
		if (dead == 0 && vary == 1){

			if (coor.x>5 && coor.x<107 && coor.y>0 && coor.y<27){//碰到牆壁死亡 

				last.x = sBody[bodyLenght - 1].x;//除去移動的最後一個位置 
				last.y = sBody[bodyLenght - 1].y;

				for (i = bodyLenght - 1; i >= 0; i--){

					if (i == 0)

						setSite(i, coor.x, coor.y);

					else

						setSite(i, sBody[i - 1].x, sBody[i - 1].y);

				}

				for (i = 0; i<bodyLenght; i++){

					printSnake(i);

				}

				Sleep(snakeSpeed);

				position(last.x, last.y); // 清除行走中的尾巴

				printf(" ");

			}
			else dead = true;


			//蛇吃到食物 
			if (sBody[0].x == foodSite.x && sBody[0].y == foodSite.y){

				isFoodEaten = false;

				if (bodyLenght<1000) bodyLenght++; // 避免身體超出陣列長度

				eatenFood++;

			}

		}

	}
	while (1){

		system("CLS");

		printf("\n你的分數為: %d\n", eatenFood * 5);

		
		break;
	
	}
	
	printf("\n\n■■■■■■■■■■      ■■■                    ■■     ■■■■■■\n■■■■■■■■■■      ■■■■                  ■■     ■■    ■■■\n");
	printf("■■                      ■■  ■■                ■■     ■■       ■■■\n■■                      ■■    ■■              ■■     ■■         ■■■\n");
	printf("■■                      ■■      ■■            ■■     ■■             ■■\n■■■■■■■■■■      ■■        ■■          ■■     ■■              ■■\n");
	printf("■■■■■■■■■■      ■■          ■■        ■■     ■■              ■■\n■■                      ■■            ■■      ■■     ■■              ■■\n");
	printf("■■                      ■■              ■■    ■■     ■■             ■■\n■■                      ■■                ■■  ■■     ■■         ■■■\n");
	printf("■■                      ■■                  ■■■■     ■■       ■■■\n■■■■■■■■■■      ■■                    ■■■     ■■    ■■■\n");
	printf("■■■■■■■■■■      ■■                    ■■■     ■■■■■■\n");
system("pause");
system("CLS");

}
int five()
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
		system("CLS");
		//顯示棋盤**************************************************************************************************
		show_Chessboard(CB, 7);

		//判斷玩家A是否勝利*****************************************************************************************
		if (judge(CB, 7)){
			printf("\n恭喜玩家 %s 勝利！！\n", nameA);
			getchar();
			//getchar();
			system("pause");
			system("CLS");
			break; //跳出到最外層的while
		}//death!!!

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
				puts("下子失敗，請重新找新位置下子");
				continue;  //下子不成功，重新下子
			}

		}
		system("CLS");
		//顯示棋盤*************************************************************************************************
		show_Chessboard(CB, 7);

		//判斷玩家B是否勝利****************************************************************************************
		if (judge(CB, 7)){
			printf("\n恭喜玩家 %s 勝利！！ \n", nameB);
			getchar();
		//	getchar();
			system("pause");
			system("CLS");
			break; //跳出到最外層的while
		}//death!!!

	}
	return 0;

}
