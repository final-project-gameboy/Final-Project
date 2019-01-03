#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//�ѽL��l��
//Chessboard=�ѽL,ln=�ѽL�e��
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

//�D��?
int main()
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

		//��ܴѽL**************************************************************************************************
		show_Chessboard(CB, 7);

		//�P�_���aA�O�_�ӧQ*****************************************************************************************
		if (judge(CB, 7)){
			printf("\n���ߪ��a %s ���\���o�ӧQ�I�I\n", nameA);
			getchar();
			getchar();
			break; //���X��̥~�h��while
		}//gameover!!!

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
				puts("�U�l��?�A?���s?�w��m�U�l");
				continue;  //�U�l�����\�A���s�U�l
			}

		}

		//��ܴѽL*************************************************************************************************
		show_Chessboard(CB, 7);

		//�P�_���aB�O�_�ӧQ****************************************************************************************
		if (judge(CB, 7)){
			printf("\n���ߪ��a %s ���\���o�`�Q�I�I \n", nameA);
			getchar();
			getchar();
			break; //���X��̥~�h��while
		}//gameover!!!

	}

	return 0;

}
