// MineSweeper Game  --> The Goal is to expose all the blanks except the bombs that are hidden, without exposing accidently a bomb//
#define _CRT_SECURE_NO_WARNINGS
#define ROWS 22
#define COLS 22
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
void printMenu();
int getMenuInput();
void paintBoard(char board[][COLS], int Rows, int Cols); // paints the board.
void initializationBoard(char board[][COLS], int Rows, int Cols); // first initialization.
void PutSpaces(char board[][COLS], int Rows, int Cols); // Workingboard initialization.
void randomizeBombs(char board[][COLS], int Rows, int Cols); // puts randomally the bombs around .
void CheckforBombs(char board[][COLS], int Rows, int Cols);// Checks if and how many bombs are around the players pick .
int FillAroundArea(char liveboard[][COLS], char workingboard[][COLS], int Rows, int Cols,int RowPick, int ColPick); // Opens everything around except for bombs or numbers//
void MinusOnecheat(char liveboard[][COLS], char workingboard[][COLS], int rows, int cols, int rowPick, int colPick, int rememberRow, int rememberCol, int* countTurns, int* counterBlanks); // a Cheat that occures when you put -1 in your RowPick and then an integer for your ColPick makes it x ( x == ColPick ) Blanks in a row //
void main() {
	char liveboard[ROWS][COLS];
	char workingboard[ROWS][COLS];
	int Choice, RowPick = 0, ColPick = 0, counterBlanks = 0, rememberCol = 0, rememberRow = 0;
	int counterTurns = 0;
	int j;
	int i;
	bool GameOver = false;
	int Rows = 0, Cols = 0;
	char FlagorOpenPick;
	int TempBomber = 0;
	Choice = getMenuInput();
	switch (Choice)
	{
	case 0:
		printf("GoodBye.\n");
		break;
	case 1:
		Rows = Cols = 8;
		break;
	case 2:
		Rows = Cols = 12;
		break;
	case 3:
		Rows = Cols = 15;
		break;
	case 4:
		printf("Please Choose A Row And Col Sizes For Your Game :\n");
		scanf("%d%d", &Rows, &Cols);
		break;
	}

	initializationBoard(liveboard, Rows, Cols);

	PutSpaces(workingboard, Rows, Cols);

	randomizeBombs(workingboard, Rows, Cols);

	CheckforBombs(workingboard, Rows, Cols);

	paintBoard(liveboard, Rows, Cols);

	while (GameOver == false)
	{
		printf("Please enter your move -- row , column and Your F/O pick:\n\n");
		
		scanf("%d%d %c", &RowPick, &ColPick, &FlagorOpenPick);
	
		while ((RowPick > Rows - 1) || (RowPick < -1) || (ColPick < 0) || (RowPick >= 0 && workingboard[RowPick][ColPick] == liveboard[RowPick][ColPick]) || ((FlagorOpenPick != 'F') && (FlagorOpenPick != 'O') && (FlagorOpenPick != 'o') && (FlagorOpenPick != 'f')))  // All the Invalid inputs / Chosen blanks that already happend.
		{
			printf("Invalid input!\n\n");
			printf("Please enter your move -- row , column and Your F/O pick:\n\n");
			scanf("%d%d %c", &RowPick, &ColPick, &FlagorOpenPick);
		}
		

		 if (FlagorOpenPick == 'f' || FlagorOpenPick == 'F')
		{
			liveboard[RowPick][ColPick] = 'F';
			paintBoard(liveboard, Rows, Cols);
		}
		 if (workingboard[RowPick][ColPick] != '*' && workingboard[RowPick][ColPick] != ' ') {

			liveboard[RowPick][ColPick] = workingboard[RowPick][ColPick];

			paintBoard(liveboard, Rows, Cols);

			counterTurns++;
		}
		
		if (RowPick == -1)
		{
			MinusOnecheat(liveboard, workingboard, Rows, Cols, RowPick, ColPick, rememberRow, rememberCol, &counterTurns, &counterBlanks);
			paintBoard(liveboard,Rows, Cols);
		}
		 if (workingboard[RowPick][ColPick] == ' ')
		{
			counterTurns += FillAroundArea(liveboard, workingboard, Rows, Cols, RowPick, ColPick);
			paintBoard(liveboard, Rows, Cols);
		}
		
		 if (workingboard[RowPick][ColPick] == '*') 
		{
			printf("You've hit a bomb!!\n Game over...\n\n");
			paintBoard(workingboard, Rows, Cols);
			GameOver = true;
			printf("Better luck next time !\n");
		}

		if (counterTurns == ((Rows*Cols) - TempBomber))
		{
			printf("Congratulations!! You've won.\n\n");
			GameOver = true;
		}
	}
}
void printMenu()
{
	printf("Welcome to Minesweeper!\n\nPlease choose one of the following options and enter it's number:\n\n");
	printf("1 - for size 8X8.\n\n");
	printf("2 - for size 12X12.\n\n");
	printf("3 - for size 15X15.\n\n");
	printf("4 - for custom size.\n\n");
	printf("0 - Exit.\n");
}
int getMenuInput()
{
	int Choice;

	printMenu();
	scanf("%d", &Choice);

	while (Choice > 4 || Choice < 0)
	{
		printf("Invalid input.\n");
		printMenu();
		scanf("%d", &Choice);
	}
	return Choice;
}
void initializationBoard(char board[][COLS], int Rows, int Cols) {

	char borderline[] = "__________________________________________\n";
	int t, k;
	for (t = 0; t < Rows; t++) {
		for (k = 0; k < Cols; k++)
		{
			board[t][k] = 'X';

		}
	}
}
void paintBoard(char board[][COLS], int Rows, int Cols) {


	printf("    ");
	int l;
	for (l = 0; l < Rows; l++)
		printf("%5d", l);
	printf("\n");

	int i, j;
	char borderline[] = "__________________________________________\n";
	for (i = 0; i < Rows; i++) {
		printf("%5d", i);

		for (j = 0; j < Cols; j++) {
			printf(" | %c ", board[i][j]);
		}
		printf("|\n");
	}
}
void PutSpaces(char board[][COLS], int Rows, int Cols) {
	int l, k;
	for (l = 0; l < Rows; l++) {
		for (k = 0; k < Cols; k++)
		{
			board[l][k] = ' ';
		}
	}

}
void randomizeBombs(char board[][COLS], int Rows, int Cols) {
	int i, j;
	int bombcount = 0;
	int TempBomber;
	TempBomber = sqrt(Rows * Cols);
	srand(time(NULL));
	while (bombcount < TempBomber)
	{
		i = rand() % TempBomber;
		j = rand() % TempBomber;
		if (board[i][j] != '*') {
			board[i][j] = '*';
			bombcount++;
		}
	}
	return TempBomber;
}
void CheckforBombs(char board[][COLS], int Rows, int Cols) {
	int i, j, countBombsaround;
	for (i = 0; i < Rows; i++)
	{
		for (j = 0; j < Cols; j++)
		{
			countBombsaround = 0;

			if (i > 0 && board[i - 1][j] == '*')
				countBombsaround++;
			if (i <= 7 && board[i + 1][j] == '*')
				countBombsaround++;
			if (j > 0 && board[i][j - 1] == '*')
				countBombsaround++;
			if (j <= 7 && board[i][j + 1] == '*')
				countBombsaround++;
			if (i <= 7 && j <= 7 && board[i + 1][j + 1] == '*')
				countBombsaround++;
			if (i > 0 && j > 0 && board[i - 1][j - 1] == '*')
				countBombsaround++;
			if (i <= 7 && j > 0 && board[i + 1][j - 1] == '*')
				countBombsaround++;
			if (i > 0 && j <= 7 && board[i - 1][j + 1] == '*')
				countBombsaround++;
			if (board[i][j] != '*') {
				board[i][j] = countBombsaround + 48;
			}
			if (board[i][j] == '0')
			{
				board[i][j] = ' ';
			}
		}

	}

}
int FillAroundArea(char liveboard[][COLS], char workingboard[][COLS], int Rows, int Cols, int RowPick, int ColPick) {
	if ((RowPick >= Rows) || (ColPick >= Cols) || (RowPick < 0) || (ColPick < 0))
	{
		return 0;
	}
	else if (liveboard[RowPick][ColPick] != 'X')
	{
		return 0;
	}
	else if (workingboard[RowPick][ColPick] == '*')
	{
		return 0;
	}
	else if (workingboard[RowPick][ColPick] >= '0' && workingboard[RowPick][ColPick] <= '9')
	{
		liveboard[RowPick][ColPick] = workingboard[RowPick][ColPick];
		return 1;
	}
	else {
		liveboard[RowPick][ColPick] = workingboard[RowPick][ColPick];
	   return 1 
		    + FillAroundArea(liveboard, workingboard, Rows, Cols, RowPick, (ColPick - 1))
			+ FillAroundArea(liveboard, workingboard, Rows, Cols, (RowPick + 1), (ColPick))
			+ FillAroundArea(liveboard, workingboard, Rows, Cols, RowPick, (ColPick + 1))
			+ FillAroundArea(liveboard, workingboard, Rows, Cols, (RowPick - 1), ColPick)
			+ FillAroundArea(liveboard, workingboard, Rows, Cols, (RowPick - 1), (ColPick - 1))
			+ FillAroundArea(liveboard, workingboard, Rows, Cols, (RowPick + 1), (ColPick + 1))
			+ FillAroundArea(liveboard, workingboard, Rows, Cols, (RowPick - 1), (ColPick + 1))
			+ FillAroundArea(liveboard, workingboard, Rows, Cols, (RowPick + 1), (ColPick - 1));
	}
} 
void MinusOnecheat(char liveboard[][COLS], char workingboard[][COLS], int rows, int cols, int rowPick, int colPick, int rememberRow, int rememberCol, int* countTurns, int* counterBlanks)
{
	int i, j;

	if (rowPick == -1 && rememberCol >= 0) {
		for (j = rememberCol; j < cols; j++) {
			if (colPick == 0) {
				rememberCol = j;
				break;
			}
			if (liveboard[rememberCol][j] == 'X' && workingboard[rememberCol][j] != '*') {
				if (liveboard[rememberRow][j] == 'X') {
					liveboard[rememberRow][j] = workingboard[rememberRow][j];
					(*countTurns)++;
				}
				colPick--;
			}
		}
		if (colPick != 0) {
			for (i = rememberRow + 1; i < rows; i++)
			{
				for (j = 0; j < cols; j++) {
					if (colPick == 0) {
						rememberCol = j;
						break;
					}
					if (liveboard[i][j] == 'X' && workingboard[i][j] != '*')
						if (liveboard[i][j] == 'X') {
							liveboard[i][j] = workingboard[i][j];
							(*counterBlanks)++;
						}
					colPick--;
				}
				if (colPick == 0) {
					rememberRow = i;
					break;
				}
			}
		}
	}
}

