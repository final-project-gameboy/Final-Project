#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <math.h>
#include <windows.h>
#define true 1
#define false 0
void menusnake();

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




typedef struct snake
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
void setSite(int i, int site_x, int site_y
	){

	sBody[i].x = site_x;
	sBody[i].y = site_y;

}


//�D����l��ܦ�m  �����O�X�o����m 
void setStartSite(){

		int i;

	sBody[0].x = sBody[1].x = sBody[2].x = sBody[3].x = sBody[4].x = 12;

	for (i = 0; i<5; i++) sBody[i].y = abs(5 - i);

}

void menusnake(){
	position(25,1);
	printf("������������������������������  << �g�Y�D�C�� >>  ������������������������������");
	position(25,16);
	printf("����������������������������������������������������������������������������������������������������");
	position(25,2);printf("��");
	position(25,3);printf("��");
	position(25,4);printf("��");
	position(25,5);printf("��");
	position(25,6);printf("��");
	position(25,7);printf("��");
	position(25,8);printf("��");
	position(25,9);printf("��");
	position(25,10);printf("��");
	position(25,11);printf("��");
	position(25,12);printf("��");
	position(25,13);printf("��");
	position(25,14);printf("��");
	position(25,15);printf("��");
	position(74,2);printf("��");
	position(74,3);printf("��");
	position(74,4);printf("��");
	position(74,5);printf("��");
	position(74,6);printf("��");
	position(74,7);printf("��");
	position(74,8);printf("��");
	position(74,9);printf("��");
	position(74,10);printf("��");
	position(74,11);printf("��");
	position(74,12);printf("��");
	position(74,13);printf("��");
	position(74,14);printf("��");
	position(74,15);printf("��");
	position(40,2);
	printf("             ����        ��");
	position(40, 3);
	printf("~~��)��    ��    ��    ��");
	position(40,4);
	printf("       ����        ����");

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

int main(int argc, char *argv[])
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
return 0;

}







