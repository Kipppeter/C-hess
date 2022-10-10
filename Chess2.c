#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define SIZE 8

int board[SIZE][SIZE];

void init_board(int board[][SIZE])
{
    int i, j;

    for (i = 0; i < SIZE; i++) 
    {
        for (j = 0; j < SIZE; j++) 
        {
            board[i][j] = 0;
        }
    }
    for (i = 0; i < SIZE; i++)
    {
		board[6][i] = 1;
		board[1][i] = 7;
	}

    board[0][0] = 8;
    board[0][1] = 10;
    board[0][2] = 9;
    board[0][3] = 11;
    board[0][4] = 12;
    board[0][5] = 9;
    board[0][6] = 10;
    board[0][7] = 8;

    board[7][0] = 2;
    board[7][1] = 4;
    board[7][2] = 3;
    board[7][3] = 5;
    board[7][4] = 6;
    board[7][5] = 3;
    board[7][6] = 4;
    board[7][7] = 2;
}

void buildBoard(int board[][SIZE])
{
	int i, j, a;
	for(i = SIZE - 1; i >= 0; i--)
	{
		for(j = 0; j < SIZE; j++)
		{
			a = board[i][j];
			// printf("A: %d", a);
			switch(a)
			{
				case 0:
				{
					printf("  ");
					break;
				}
				case 1:
				{
					printf("p ");
					break;
				}
				case 2:
				{
					printf("r ");
					break;
				}
				case 3:
				{
					printf("b ");
					break;
				}
				case 4:
				{
					printf("n ");
					break;
				}
				case 5:
				{
					printf("q ");
					break;
				}
				case 6:
				{
					printf("k ");
					break;
				}
				case 7:
				{
					printf("P ");
					break;
				}
				case 8:
				{
					printf("R ");
					break;
				}
				case 9:
				{
					printf("B ");
					break;
				}
				case 10:
				{
					printf("N ");
					break;
				}
				case 11:
				{
					printf("Q ");
					break;
				}
				case 12:
				{
					printf("K ");
					break;
				}
			}
		}
		printf("%d", i + 1);
		printf("\n");
	}
	printf("1 2 3 4 5 6 7 8 \n");
}

void move_piece(int board[][SIZE])
{
	int sX, sY, eX, eY;
	printf("Insert starting X-coordinate\n");
	scanf("%2d", &sY);
	printf("Insert starting Y-coordinate\n");
	scanf("%2d", &sX);
	printf("Insert ending X-coordinate\n");
	scanf("%2d", &eY);
	printf("Insert ending Y-coordinate\n");
	scanf("%2d", &eX);
	
	sX = sX-1;
	sY = sY-1;
	eX = eX-1;
	eY = eY-1; 

	board[eX][eY] = board[sX][sY];
	
	board[sX][sY] = 0;
}

int kingDeadCheck(void)
{
	int i, j;
	int wK = 0;
	int bK = 0;
	for(i = 0; i < SIZE; i++)
	{
		for(j = 0; j < SIZE; j++)
		{
			if(board[i][j] == 12)
				wK = 1;
			else if (board[i][j] == 6)
				bK = 1;
		}
	}
	if (bK == 0)
	{
		printf("White wins!");
		return 0;
	}
	else if (wK == 0)
	{
		printf("Black wins!");
		return 0;
	}
	return 1;
}

int main(void)
{
	init_board(board);
	buildBoard(board);
	while(1)
	{
		move_piece(board);
		buildBoard(board);
		if(kingDeadCheck() == 0)
			break;
	}
	
	
	return 0;
}
