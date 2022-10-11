#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define SIZE 8

int board[SIZE][SIZE];
int legalMoves[SIZE][SIZE];
int whoseTurn;

int Smallest(a, b)
{
	if(a < b)
		return a;
	return b;
}

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
	int sX, sY, eX, eY, piece, i, j, anyLegalMoves;
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
	
		 
		anyLegalMoves = AllowedMoves(i, sX, sY, piece);
		if(anyLegalMoves == 0)
		{
			printf("This piece can not move!\n");
			goto start;
		}
		else if(anyLegalMoves == 3)
		{
			printf("Incorrect colour piece!\n");
			goto start;
		}
		
		//printf("legalMoves table:\n");
		//for(i = 0; i < SIZE; i++)
		//{
			//for(j = 0; j < SIZE; j++)
				//printf("%d ", legalMoves[7-i][j]);
			//printf("%d\n", 8 - i);
		//}
		//printf("1 2 3 4 5 6 7 8\n");
		
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
	if (whoseTurn == 0)
		whoseTurn = 1;
	else
		whoseTurn = 0;
}

int AllowedMoves( i, Y, X, piece)
{
	int n, j, anyLegalMoves;
	int minX = 0;
	int maxX = 7;
	int minY = 0;
	int maxY = 7;
	int d1 = 10;
	int d2 = 10;
	int d3 = 10;
	int d4 = 10;
	for(n = 0; n < SIZE; n++)
	{
		for(j = 0; j < SIZE; j++)
			legalMoves[n][j] = 0;
	}
	// printf("piece: %d\n", piece); // debug
	
	// correct colour piece checker
	if((whoseTurn == 0) && (piece < 6))
		return 3;
	else if((whoseTurn == 1) && (piece > 5))
		return 3;
	
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
			else if(board[Y-2][X] != 0) // check if anything in the way
			{
				legalMoves[Y-2][X] = 0;
			}
			// check for takes
			if((X + 1 < SIZE) && (board[Y-1][X+1] > 5) && (board[Y-1][X+1] > 0))
				legalMoves[Y-1][X+1] = 1;
			if((X - 1 >= 0) && (board[Y-1][X-1] > 5) && (board[Y-1][X-1] > 0))
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
			else if(board[Y+2][X] != 0) // check if anything in the way
			{
				legalMoves[Y+2][X] = 0;
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
			for(j = 0; j < SIZE; j++)
			{
				legalMoves[Y][j] = 1;
				legalMoves[j][X] = 1;
			}
			legalMoves[Y][X] = 0; // can't move to own position
			
			
			// piece-in-the-way check
			for(j = 1; j < SIZE; j++)
			{
				
				if(minY == 0)
				{
					if(board[Y-j][X] > 0)
						minY = Y-j;
				}
				if(maxY == 7)
				{
					if(board[Y+j][X] > 0)
						maxY = j+Y;
				}
				if(maxX == 7)
				{
					if(board[Y][X+j] > 0)
						maxX = j+X;
				}
				if(minX == 0)
				{
					if(board[Y][X-j] > 0)
						minX = X-j;
				}
			}
			printf("MINY %d\n MAXY %d\n MAXX %d\n MINX %d\n", minY, maxY, maxX, minX); // DEBUGER
			
			// board zeroer
			for(j = 0; j < SIZE; j++)
			{
				if(j < minX)
				{
					legalMoves[Y][j] = 0;
					// printf("MinX changed!\n");
				}
				if(j < minY)
				{
					legalMoves[j][X] = 0;
					// printf("MinY changed!\n");
				}
			}
			for(j = 7; j > 0; j--)
			{
				if(j > maxY)
				{
					legalMoves[j][X] = 0;
					// printf("MaxY changed!\n");
				}
				if(j > maxX)
				{
					legalMoves[Y][j] = 0;
					// printf("MaxX changed!\n");
				}
			}
			if((piece == 5) || (piece == 11))
				goto bishop;
			break;
		}
		case 8:
		{
			goto rook;
		}
		case 3:
		{
			bishop:
			
			// diagonal move allower
			for(j = 1; j < SIZE; j++)
			{
				if((X+j < SIZE) && (Y+j < SIZE))
					legalMoves[Y+j][X+j] = 1;
				if((X-j >= 0) && (Y-j >= 0))
					legalMoves[Y-j][X-j] = 1;
				if((X+j < SIZE) && (Y-j >= 0))
					legalMoves[Y-j][X+j] = 1;
				if((X-j >= 0) && (Y+j < SIZE))
					legalMoves[Y+j][X-j] = 1;
			}
			
			// blocked move denyer
			
			for(j = 1; j < SIZE; j++)
			{
				if((d3 == 10) && (Y-j >= 0) && (X-j >= 0))
				{
					if(board[Y-j][X-j] > 0) 
						d3 = j;
				}
				if((d4 == 10) && (Y+j < SIZE) && (X-j >= 0))
				{
					if(board[Y+j][X-j] > 0)
						d4 = j;
				}
				if((d1 == 10) && (Y+j < SIZE) && (X+j < SIZE))
				{
					if(board[Y+j][X+j] > 0)
						d1 = j;
				}
				if((d2 == 10) && (Y-j >= 0) && (X+j < SIZE)) 
				{
					if(board[Y-j][X+j] > 0)
						d2 = j;
				}
			}
			// printf("d1 = %d\nd2 = %d\nd3 = %d\nd4 = %d\n", d1,d2,d3,d4);
			// board zeroer
			for(j = 0; j < SIZE; j++)
			{
				if(j >= d1)
					legalMoves[Y+j][X+j] = 0;
				if(j >= d3)
					legalMoves[Y-j][X-j] = 0;
				if(j >= d2)
					legalMoves[Y-j][X+j] = 0;
				if(j >= d4)
					legalMoves[Y+j][X-j] = 0;
			}
			
			break;
		}
		case 9:
		{
			goto bishop;
		}
		case 4:
		{
			knight:
			if((X+2 < SIZE) && (Y+1 < SIZE) && (board[Y+1][X+2] == 0))
				legalMoves[Y+1][X+2] = 1;
			if((X+2 < SIZE) && (Y-1 >= 0) && (board[Y-1][X+2] == 0))
				legalMoves[Y-1][X+2] = 1;
			if((X-2 >= 0) && (Y+1 < SIZE) && (board[Y+1][X-2] == 0))
				legalMoves[Y+1][X-2] = 1;
			if((X-2 >= 0) && (Y-1 >= 0) && (board[Y-1][X-2] == 0))
				legalMoves[Y-1][X-2] = 1;
			if((Y+2 < SIZE) && (X+1 < SIZE) && (board[Y+2][X+1] == 0))
				legalMoves[Y+2][X+1] = 1;
			if((Y+2 < SIZE) && (X-1 >= 0) && (board[Y+2][X-1] == 0))
				legalMoves[Y+2][X-1] = 1;
			if((Y-2 >= 0) && (X+1 < SIZE) && (board[Y-2][X+1] == 0))
				legalMoves[Y-2][X+1] = 1;
			if((Y-2 >= 0) && (X-1 >= 0) && (board[Y-2][X-1] == 0))
				legalMoves[Y-2][X-1] = 1;
			break;
		}
		case 10:
		{
			goto knight;
		}
		case 5:
		{
			queen:
			goto rook;
			/*
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
			 */
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
	// own piece take-ability remover
	for(i = 0; i < SIZE; i++)
		{
			for(j = 0; j < SIZE; j++)
			{
				if((board[i][j] > 5) && (whoseTurn == 0))
					legalMoves[i][j] = 0;
				else if((board[i][j] < 6) && (whoseTurn == 1) && (board[i][j] != 0))
					legalMoves[i][j] = 0;
			}
		}
	
	printf("legalMoves table:\n");
		for(i = 0; i < SIZE; i++)
		{
			for(j = 0; j < SIZE; j++)
				printf("%d ", legalMoves[7-i][j]);
			printf("%d\n", 8 - i);
		}
		printf("1 2 3 4 5 6 7 8\n");
	// check if any legal moves with this piece
	anyLegalMoves = 0;
	for(i = 0; SIZE > i; i++)
	{
		for(j = 0; SIZE > j; j++)
		{
			anyLegalMoves = legalMoves[i][j];
			if(anyLegalMoves == 1)
				return 1;
		}
	}
	return 0;
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
	board[3][3] = 2;
	buildBoard(board);
	whoseTurn = 0;
	while(1)
	{
		move_piece(board);
		buildBoard(board);
		if(kingDeadCheck() == 0)
			break;
	}
	return 0;
}
