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


//��ܴѽL**************************************************************************************************
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

//�U�Ѥl
//�U�Ѧ��\return 1 �S���\return 0
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

//�P�_�O�_���L
//��return 1 �S��return 0
int full_Chess(char Chessboard[][7], int ln)
{
	int i = 0, j = 0;
	for (i = 0; i<ln; ++i){
		for (j = 0; j<ln; ++j){
			if ('\t' == Chessboard[i][j]){
				return 0;  //����
			}
		}
	}

	return 1;//���F

}


//�P?�O�_�s�����l�B�@��
//Chessboard=�ѽL,ln=�ѽL�e��,(XS,YS)��V�P�_�_�I�y��,(dx,dy)��V�W�q
//�����\return 1�A?��return 0
int judge_line(char Chessboard[][7], int ln, int XS, int YS, int dx, int dy)
{
	assert((Chessboard != NULL) && (ln > 0));

	if ((XS <ln) && (YS<ln)             //�_?�I�y�Цb�ѽL��
		&& (XS >= 0) && (YS >= 0)
		&& (dx != 0 || dy != 0))        //�y�мW�q���P�ɬ�0
	{

		if (((XS + dx * 4) > ln) || ((XS + dx * 4)<0) || //�P??�I�y��
			((YS + dy * 4)>ln) || ((YS + dy * 4) < 0) || //�b�ѽL�~
			('\t' == Chessboard[XS][YS]))
		{
			return 0;  //���b�ѽL?or�_�I?�U�Ѥl
		}


		else
		{
			for (int i = 1; i < 5; ++i){
				if (Chessboard[XS][YS] != Chessboard[XS + (dx * i)][YS + (dy * i)]){
					return 0;  //�p�G���O�s��5�Ӥ@�˪�
				}
			}
			return 1;
		}
	}
	return 0;  //��L��?
}


//�P�_���
//Chessboard �ѽL�Aln=�ѽL�e��
//?�Freturn 1�A�S�� return 0
int judge(char Chessboard[][7], int ln)//ln=7
{
	assert((NULL != Chessboard) && (ln>0));

	int i = 0, j = 0;
	//�a�V�����l�s�u�P?*********************************************
	for (i = 0; i<(ln - 4); ++i){
		for (j = 0; j<ln; ++j){
			if (judge_line(Chessboard, ln, i, j, 1, 0)){
				return 1;
			}
		}
	}

	//?�V�����l�s�u�P?**********************************************
	for (i = 0; i<ln; ++i){
		for (j = 0; j<(ln - 4); ++j){
			if (judge_line(Chessboard, ln, i, j, 0, 1)){
				return 1;
			}
		}
	}

	//���W��k�U�����l�s�u�P?*****************************************
	for (i = 0; i<(ln - 4); ++i){
		for (j = 0; j<(ln - 4); ++j){
			if (judge_line(Chessboard, ln, i, j, 1, 1)){
				return 1;
			}
		}
	}

	//���U��k�W�����l�s�u�P?******************************************
	for (i = ln - 1; i>(ln - 4); --i){
		for (j = 0; j <(ln - 4); ++j){
			if (judge_line(Chessboard, ln, i, j, -1, 1)){
				return 1;
			}
		}
	}

	return 0;  //?��?
}
void position(int xpos, int ypos) //���ʴ�Цܫ��w��m 
{

	COORD scrn;

	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);

	scrn.X = xpos; scrn.Y = ypos;

	SetConsoleCursorPosition(hOuput, scrn);
}



void showCursor(int visible)//�s�{��²������Ϊ����å��з��N�X�C 
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



Snake sBody[1000]; //���W�L�̤j�}�C����


//�D������
void printSnake(int i)
{

	position(sBody[i].x, sBody[i].y);

	printf("��");

}


//���
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


//�k�誺�������
void Information(int food, int speed)
{
	position(40, 28);
	printf("����: %d", food * 5);
	position(50, 28);
	if (speed == 300) printf("�t��: %3d (�̧C�t)", 310 - speed);
	else if (speed == 10) printf("�t��: %3d (�̰��t)", 310 - speed);
	else printf("�t��: %3d              ", 310 - speed);
}


//���骺�y�� 
void setSite(int i, int site_x, int site_y)
{

	sBody[i].x = site_x;

	sBody[i].y = site_y;

}


//�D����l��ܦ�m  �����O�X�o����m 
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
    position(25,a);printf("��");
	position(74,a);printf("��");
}
	position(25,1);
	printf("������������������������  �� ��  �C �� BOY  �� ����������������������������");
	position(25,25);
	printf("����������������������������������������������������������������������������������������������������");
	position(32, 5);
	printf("�w��Ө�C��BOY");
	position(32, 6);
	printf("�b�o�̥i�H�ɱ��������h�����j�����p�C��");
	position(32, 8);
	printf("�C���C��:");
	position(32, 9);
	printf("1.�q���C��");
	position(32, 10);
	printf("2.�׷��K�X");
	position(32, 11);
	printf("3.�g���D");
	position(32, 12);
	printf("4.���H�若���l��");
	position(32, 13);
	printf("5.���}�C��BOY");
	position(32, 15);
	printf("�п�ܷQ�n�C�����C��:");
	scanf(" %c", &choice1);
	

		switch (choice1)
		{
		case '1':
			system("CLS");
			puzzle();
			break;
		case '2':
			system("CLS");
			printf("�׷��K�X");
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
	printf("�ϥ���L�Ǫ��E�c��1,2,3,4,6,7,8,9�����ϧ�\n����U�ؼ���ɨ���������ؼ���N�|1�M0�ഫ\n�C���ت��O�N�ϧΥ����令1�N���!\n");
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
	printf("\n\n\t%c�@%c�@%c\n", conversion(pPillar[6]), conversion(pPillar[5]), conversion(pPillar[4]));
	printf("\t%c�@�@ %c\n", conversion(pPillar[7]), conversion(pPillar[3]));
	printf("\t%c�@%c�@%c\n\n", conversion(pPillar[0]), conversion(pPillar[1]), conversion(pPillar[2]));
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
	printf("������������������������������  << �g�Y�D�C�� >>  ������������������������������");
	position(25,16);
	printf("����������������������������������������������������������������������������������������������������");
	for(int a=2;a<16;a++){
    position(25,a);printf("��");
	position(74,a);printf("��");
}

	position(40,2);	printf("             ����        ��");
	position(40, 3);printf("~~��)��    ��    ��    ��");
	position(40,4);	printf("       ����        ����");
	position(40, 5);
	printf("�@�ӥؼЬ�5��");
	position(40, 7);
	printf("����W �U �� �k");
	position(40, 9);
	printf("Q��ӼW�[�t��");
	position(40, 10);
	printf("E��Ӵ�ֳt��");
	position(40, 12);
	printf("T�� �Ȱ�");
	position(40,14);
	system("pause");
	system("CLS");
}
int snake()
{
	int startBodyLenght = 5, startEatenFood = 0, bodyLenght, eatenFood;
	int FirstKey, SecondKey;
	int i, j, dead = false, isFoodEaten = false, vary = false;
	int direction = 2; // ��V�V�U 
	int snakeSpeed = 100;
	char requirements = 'y';
	Snake foodSite, coor, last;
	menusnake();
	srand(time(NULL));
	showCursor(0);//���������r�����I 
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


	//��R�}�l (�]�����X�j��ҥH��U�@�B�J) 
	do{
		position(50, 10);
		printf("R��-�}�l");
		requirements = getch();
		position(50, 10);
		printf("             ");
	} while (requirements != 'r');



	while (!dead){

		//��s�O���O
		Information(eatenFood, snakeSpeed);

		// �p�G�S����, �H����X�@�ӭ�������m
		if (!isFoodEaten){

			foodSite.x = rand() % 49 * 2 + 6;
			foodSite.y = rand() % 25 + 2;

			isFoodEaten = true;

		}

		position(foodSite.x, foodSite.y);

		printf("��");

		vary = false;


		// ��L�ާ@ 
		if (kbhit()){

			FirstKey = getch();

			//224�O��V�䪺extended key
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

			//P��Ȱ� 
			if (FirstKey == 't' || FirstKey == 'T'){

				do{

					position(50, 10);
					printf("�Ȱ�");

					requirements = getch();

					position(50, 10);
					printf("          ");

				} while (requirements != 't' && requirements != 'T');

			}
			//Q���W�[�t�� 
			if (FirstKey == 'q' || FirstKey == 'Q'){

				if (snakeSpeed > 10) snakeSpeed -= 10;

				FirstKey = '\0';

			}
			//E����ֳt�� 
			if (FirstKey == 'e' || FirstKey == 'E'){

				if (snakeSpeed < 300) snakeSpeed += 10;

				FirstKey = '\0';

			}

		}
		else { // �S������ʧ@�h���۲{��V�e�i

			switch (direction){

			case 1: //�W 

				coor.y--;

				direction = 1;

				break;

			case 2: //�U 

				coor.y++;

				direction = 2;

				break;

			case 3: //�� 

				coor.x -= 2;

				direction = 3;

				break;

			case 4: //�k 

				coor.x += 2;

				direction = 4;

				break;

			}

			vary = true;

		}

		//�I��ۤv���鵲���C�� 
		for (i = 1; i<bodyLenght; i++){

			if (coor.x == sBody[i].x && coor.y == sBody[i].y)

				dead = true;
		}
		//�D���� 
		if (dead == 0 && vary == 1){

			if (coor.x>5 && coor.x<107 && coor.y>0 && coor.y<27){//�I��������` 

				last.x = sBody[bodyLenght - 1].x;//���h���ʪ��̫�@�Ӧ�m 
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

				position(last.x, last.y); // �M���樫��������

				printf(" ");

			}
			else dead = true;


			//�D�Y�쭹�� 
			if (sBody[0].x == foodSite.x && sBody[0].y == foodSite.y){

				isFoodEaten = false;

				if (bodyLenght<1000) bodyLenght++; // �קK����W�X�}�C����

				eatenFood++;

			}

		}

	}
	while (1){

		system("CLS");

		printf("\n�A�����Ƭ�: %d\n", eatenFood * 5);

		
		break;
	
	}
	
	printf("\n\n��������������������      ������                    ����     ������������\n��������������������      ��������                  ����     ����    ������\n");
	printf("����                      ����  ����                ����     ����       ������\n����                      ����    ����              ����     ����         ������\n");
	printf("����                      ����      ����            ����     ����             ����\n��������������������      ����        ����          ����     ����              ����\n");
	printf("��������������������      ����          ����        ����     ����              ����\n����                      ����            ����      ����     ����              ����\n");
	printf("����                      ����              ����    ����     ����             ����\n����                      ����                ����  ����     ����         ������\n");
	printf("����                      ����                  ��������     ����       ������\n��������������������      ����                    ������     ����    ������\n");
	printf("��������������������      ����                    ������     ������������\n");
system("pause");
system("CLS");

}
int five()
{
	char CB[7][7];
	char nameA[50] = "���aA";
	char nameB[50] = "���aB";
	int x = -1, y = -1;

	//�ѽL��l��**************************************************************************************************
	init_Chessboard(CB, 7);

	//�]�w���a�W�l*************************************************************************************************
	printf("�п�J���aA���W�r:");
	scanf("%s", nameA);
	printf("�п�J���aB���W�r:");
	scanf("%s", nameB);

	//��ܴѽL*****************************************************************************************************
	show_Chessboard(CB, 7);

	while (1){
		//�P�_�ѽL�O�_���F
		if (full_Chess(CB, 7)){
			puts("\n��?�w?�A�U���A?�I");
			break; //���X��̥~�h��while
			
		}


		//A�U��****************************************************************************************************
		while (1){
			printf("\n�Ъ��a %s �U�l @\n", nameA);
			printf("�a�y��=");
			scanf("%d", &x);
			printf("��y��=");
			scanf("%d", &y);

			if (play_five(CB, 7, x, y, '@')){
				break;
			}
			else
			{
				puts("�U�l���ѡA�Э��s��s��m�U�l");
				continue;  //�U�l�����\�A���s�U�l
			}
		}
		system("CLS");
		//��ܴѽL**************************************************************************************************
		show_Chessboard(CB, 7);

		//�P�_���aA�O�_�ӧQ*****************************************************************************************
		if (judge(CB, 7)){
			printf("\n���ߪ��a %s �ӧQ�I�I\n", nameA);
			getchar();
			//getchar();
			system("pause");
			system("CLS");
			break; //���X��̥~�h��while
		}//death!!!

		//B�U��****************************************************************************************************
		while (1){
			printf("\n�Ъ��a %s �U�l O\n", nameB);
			printf("�a�y��=");
			scanf("%d", &x);
			printf("��y��=");
			scanf("%d", &y);

			if ((play_five(CB, 7, x, y, 'O'))){
				break;
			}
			else
			{
				puts("�U�l���ѡA�Э��s��s��m�U�l");
				continue;  //�U�l�����\�A���s�U�l
			}

		}
		system("CLS");
		//��ܴѽL*************************************************************************************************
		show_Chessboard(CB, 7);

		//�P�_���aB�O�_�ӧQ****************************************************************************************
		if (judge(CB, 7)){
			printf("\n���ߪ��a %s �ӧQ�I�I \n", nameB);
			getchar();
		//	getchar();
			system("pause");
			system("CLS");
			break; //���X��̥~�h��while
		}//death!!!

	}
	return 0;

}
