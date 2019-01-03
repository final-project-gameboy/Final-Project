#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include <windows.h>

void start(int *pPillar,int size);
void play(int *pPillar,int size);
void show(int *pPillar,int size);
char conversion(int temp);
bool endflag(int *pPillar,int size);
void gotoxy(int xpos, int ypos);
int main()
{
	int size=8,Pillar[size];
	srand(time(NULL));
	start(Pillar,size);
	play(Pillar,size);
	printf("       YOU WIN!!\n\n");
	system("pause");
	return 0;
}
void start(int *pPillar,int size)
{
	int i;
	for(i=0;i<size;i++)
		pPillar[i]=rand()%2;
	printf("使用鍵盤旁的九宮格1,2,3,4,6,7,8,9對應圖形\n當按下目標鍵時其附近兩顆鍵目標鍵將會1和0轉換\n遊戲目的是將圖形全部改成1就獲勝!\n");		
	show(pPillar,size);
}
void play(int *pPillar,int size)
{
	char key;
	int i,temp;  
	key=getch();  //*1=49(0),*2=50(1),*3=51(2),4=52(5),6=54(7),*7=55(6),8=56(5),9=57(3) 
	for(i=-1;i<2;i++)
	{
		if(key>=49 && key<=57 && key!=53) temp=key-'1';
		else break;
		temp=(temp==3)?7+i:(temp==5)?3+i:(temp==7)?5+i:(temp==8)?4+i:temp+i;
		pPillar[(temp<0)?7:(temp>7)?0:temp]=!pPillar[(temp<0)?7:(temp>7)?0:temp];
	}
	show(pPillar,size); 	
	if(endflag(pPillar,size)!=1)	play(pPillar,size);
}
void show(int *pPillar,int size)
{
	int i;
	gotoxy(8,2); 
	printf("\n\n\t%c　%c　%c\n",conversion(pPillar[6]),conversion(pPillar[5]),conversion(pPillar[4]));
	printf("\t%c　　 %c\n",conversion(pPillar[7]),conversion(pPillar[3]));
	printf("\t%c　%c　%c\n\n",conversion(pPillar[0]),conversion(pPillar[1]),conversion(pPillar[2]));
}
char conversion(int temp)
{
	if (temp==1) return 'I';
	else return 'O';
}
bool endflag(int *pPillar,int size)
{
	int i,count=0;
	for(i=0;i<size;i++)
		(pPillar[i]==1)?count++:0;
	if(count==8) return 1;
	else return 0;
}
void gotoxy(int xpos, int ypos) //移動游標至指定位置 
{

	COORD scrn;

	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);

	scrn.X = xpos; scrn.Y = ypos;

	SetConsoleCursorPosition(hOuput, scrn);
}
