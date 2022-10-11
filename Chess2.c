#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define SIZE 8

int board[SIZE][SIZE];
int legalMoves[SIZE][SIZE];

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
	int sX, sY, eX, eY, piece, i, j;
	int validMove = 0;
	while(validMove == 0)
	{
		start:
		printf("Insert starting X-coordinate\n");
		scanf("%2d", &sY);
		printf("Insert starting Y-coordinate\n");
		scanf("%2d", &sX);
	
		sX = sX-1;
		sY = sY-1;
		
		piece = board[sX][sY];
		printf("\nCurrent piece: %d\n", piece); // bugstomper
		if (piece == 0)
		{
			printf("Empty spaces can not move!\n");
			goto start;
		}
	
		 
		
		AllowedMoves(i, sX, sY, piece);
		
		printf("DEBUG legalMoves table:\n");
		for(i = 0; i < SIZE; i++)
		{
			for(j = 0; j < SIZE; j++)
				printf("%d ", legalMoves[7-i][j]);
			printf("\n");
		}
		printf("\n");
		
		printf("Insert ending X-coordinate\n");
		scanf("%2d", &eY);
		printf("Insert ending Y-coordinate\n");
		scanf("%2d", &eX);
		
		eX = eX-1;
		eY = eY-1;
		
		validMove = legalMoves[eX][eY];
		if(validMove == 0)
			printf("\n\nError! Invalid move!\n");
	}
	board[eX][eY] = board[sX][sY];
	
	board[sX][sY] = 0;
}

int AllowedMoves( i, Y, X, piece)
{
	int n, j;
	int minX, maxX, minY, maxY;
	for(n = 0; n < SIZE; n++)
	{
		for(j = 0; j < SIZE; j++)
			legalMoves[n][j] = 0;
	}
	
	// printf("piece: %d\n", piece); // debug
	
	switch(piece)
	{
		case 1:
		{
			if(Y == 6) // check if 2 moves can be made
			{
				legalMoves[Y-2][X] = 1;
			}
			legalMoves[Y-1][X] = 1;
			if(board[Y-1][X] != 0) // check if anything in the way
			{
				legalMoves[Y-2][X] = 0;
				legalMoves[Y-1][X] = 0;
			}
			// check for takes
			if((X + 1 < SIZE) && (board[Y-1][X+1] < 6) && (board[Y-1][X+1] > 0))
				legalMoves[Y-1][X+1] = 1;
			if((X - 1 >= 0) && (board[Y-1][X-1] < 6) && (board[Y-1][X-1] > 0))
				legalMoves[Y-1][X-1] = 1;
			break;
		}
		case 7:
		{
			if(Y == 1) // check if 2 moves can be made
			{
				legalMoves[Y+2][X] = 1;
			}
			legalMoves[Y+1][X] = 1;
			
			if(board[Y+1][X] != 0) // check if anything in the way
			{
				legalMoves[Y+2][X] = 0;
				legalMoves[Y+1][X] = 0;
			}
			// check for takes
			if((X + 1 < SIZE) && (board[Y+1][X+1] < 6) && (board[Y+1][X+1] > 0))
				legalMoves[Y+1][X+1] = 1;
			if((X - 1 >= 0) && (board[Y+1][X-1] < 6) && (board[Y+1][X-1] > 0))
				legalMoves[Y+1][X-1] = 1;
			break;
		}
		case 2:
		{
			rook:
			// add check to see if pieces in the way
			for(j = 0; j < SIZE; j++)
			{
				legalMoves[Y][j] = 1;
				legalMoves[j][X] = 1;
			}
			break;
		}
		case 8:
		{
			goto rook;
		}
		case 3:
		{
			bishop:
			for(j = 0; j < SIZE; j++)
			{
				while((X+j < SIZE) && (Y+j < SIZE))
					legalMoves[Y+j][X+j] = 1;
				while((X+j >= 0) && (Y+j >= 0))
					legalMoves[Y-j][X-j] = 1;
			}
			break;
		}
		case 9:
		{
			goto bishop;
		}
		case 4:
		{
			if((X+2 < SIZE) && (Y+1 < SIZE))
				legalMoves[Y+1][X+2] = 1;
			if((X+2 < SIZE) && (Y-1 >= 0))
				legalMoves[Y-1][X+2] = 1;
			if((X-2 >= 0) && (Y+1 < SIZE))
				legalMoves[Y+1][X-2] = 1;
			if((X-2 >= 0) && (Y-1 >= 0))
				legalMoves[Y-1][X+2] = 1;
			if((Y+2 < SIZE) && (X+1 < SIZE))
				legalMoves[Y+2][X+1] = 1;
			if((Y+2 < SIZE) && (X-1 >= 0))
				legalMoves[Y+2][X-1] = 1;
			if((Y-2 >= 0) && (X+1 < SIZE))
				legalMoves[Y-2][X+1] = 1;
			if((Y-2 >= 0) && (X-1 >= 0))
				legalMoves[Y-2][X-1] = 1;
			break;
		}
		case 5:
		{
			queen:
			for(j = 0; j < SIZE; j++)
			{
				while((X+j < SIZE) && (Y+j < SIZE))
					legalMoves[Y+j][X+j] = 1;
				while((X+j >= 0) && (Y+j >= 0))
					legalMoves[Y-j][X-j] = 1;
			}
			for(j = 0; j < SIZE; j++)
			{
				legalMoves[Y][j] = 1;
				legalMoves[j][X] = 1;
			}
			break;
		}
		case 11:
		{
			goto queen;
		}
		case 6:
		{
			king:
			for(j = Y - 1; j <= Y + 1; j++)
			{
				for(n = X - 1; n <= X + 1; n++)
					legalMoves[j][n] = 1;
			}
			legalMoves[Y][X] = 0;
			if(X - 1 < 0)
			{
					legalMoves[Y][X-1] = 0;
					legalMoves[Y-1][X-1] = 0;
					legalMoves[Y+1][X-1] = 0;
			}
			if(X + 1 > SIZE)
			{
				legalMoves[Y][X+1] = 0;
				legalMoves[Y-1][X+1] = 0;
				legalMoves[Y+1][X+1] = 0;
			}
			if(Y - 1 < 0)
			{
					legalMoves[Y-1][X] = 0;
					legalMoves[Y-1][X-1] = 0;
					legalMoves[Y-1][X+1] = 0;
			}
			if(Y + 1 > SIZE)
			{
				legalMoves[Y+1][X] = 0;
				legalMoves[Y+1][X+1] = 0;
				legalMoves[Y+1][X-1] = 0;
			}
			break;
		}
		case 12:
		{
			goto king;
		}
	}
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
