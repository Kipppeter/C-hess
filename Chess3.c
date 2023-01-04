#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>

#define SIZE 8
#define NUM_SAVEDMOVES 100

#define EMPTYSPACE 0
#define BLACKPAWN 1
#define BLACKROOK 2
#define BLACKBISHOP 3
#define BLACKKNIGHT 4
#define BLACKKING 6
#define BLACKQUEEN 5
#define WHITEPAWN 7
#define WHITEROOK 8
#define WHITEBISHOP 9
#define WHITEKNIGHT 10
#define WHITEKING 12
#define WHITEQUEEN 11

#define WHITEMOVE 0
#define BLACKMOVE 1


int board[SIZE][SIZE];
int prevBoard[SIZE][SIZE];
int legalMoves[SIZE][SIZE];
int madeMoves[2][NUM_SAVEDMOVES];
int moveNumber = 0;
int whoseTurn = WHITEMOVE;
int whiteCheck = 0;
int blackCheck = 0;
int whiteKingAlive = 1;
int blackKingAlive = 1;


void init_board(void);
void buildBoard(void);
void move_piece(void);
int AllowedMoves(int whoChecks, int Y, int X, int pieceType);
void PrintLegalMoves(void);
void IsCheck(void);
void UpdatePrev(void);
void RevertCurrent(void);
void KingDeadCheck(void);


int main(void)
{
	init_board();
	while(whiteKingAlive == 1 && blackKingAlive == 1)
	{
		buildBoard();
		move_piece();
		KingDeadCheck();
	}
	return 0;
}

void init_board(void)
{
	int i, j;

	for(i = 0; i < SIZE; i++)
	{
		for(j = 0; j < SIZE; j++)
			board[i][j] = EMPTYSPACE;
	}

	//Initialize black pieces
	board[0][0] = BLACKROOK;
	board[0][1] = BLACKKNIGHT;
	board[0][2] = BLACKBISHOP;
	board[0][3] = BLACKQUEEN;
	board[0][4] = BLACKKING;
	board[0][5] = BLACKBISHOP;
	board[0][6] = BLACKKNIGHT;
	board[0][7] = BLACKROOK;
	for(j = 0; j < SIZE; j++)
		board[1][j] = BLACKPAWN;

	// Initialize white pieces
	board[7][0] = WHITEROOK;
	board[7][1] = WHITEKNIGHT;
	board[7][2] = WHITEBISHOP;
	board[7][3] = WHITEQUEEN;
	board[7][4] = WHITEKING;
	board[7][5] = WHITEBISHOP;
	board[7][6] = WHITEKNIGHT;
	board[7][7] = WHITEROOK;
	for(j = 0; j < SIZE; j++)
		board[6][j] = WHITEPAWN;
}

void buildBoard(void)
{
	int i, j;
	printf("\n    A   B   C   D   E   F   G   H \n");
	printf("  +---+---+---+---+---+---+---+---+\n");
	for(i = 0; i < SIZE; i++)
	{
		printf("%d ", SIZE - i);
		for(j = 0; j < SIZE; j++)
		{
			printf("|");
			switch(board[i][j])
			{
				case EMPTYSPACE:
				{
					printf("   ");
					break;
				}
				case BLACKPAWN:
				{
					printf(" p ");
					break;
				}
				case BLACKROOK:
				{
					printf(" r ");
					break;
				}
				case BLACKBISHOP:
				{
					printf(" b ");
					break;
				}
				case BLACKKNIGHT:
				{
					printf(" n ");
					break;
				}
				case BLACKKING:
				{
					printf(" k ");
					break;
				}
				case BLACKQUEEN:
				{
					printf(" q ");
					break;
				}
				case WHITEPAWN:
				{
					printf(" P ");
					break;
				}
				case WHITEROOK:
				{
					printf(" R ");
					break;
				}
				case WHITEBISHOP:
				{
					printf(" B ");
					break;
				}
				case WHITEKNIGHT:
				{
					printf(" N ");
					break;
				}
				case WHITEKING:
				{
					printf(" K ");
					break;
				}
				case WHITEQUEEN:
				{
					printf(" Q ");
					break;
				}
				default:
				{
					printf("   ");
					break;
				}
			}
		}
		printf("|\n");
		printf("  +---+---+---+---+---+---+---+---+\n");
	}
}

void move_piece(void)
{
	char startCol, endCol;
	int startRow, endRow;
	int startX, startY, endX, endY;
	int validMove = 0;

	while(validMove == 0)
	{
		printf("Enter the location of the piece you want to move (e.g. A1): ");
		scanf(" %c%d", &startCol, &startRow);
		startCol = toupper(startCol);
		startX = startCol - 'A';
		startY = SIZE - startRow;
		
		if(whoseTurn == WHITEMOVE && board[startY][startX] < 7)
		{
			printf("It's white's turn! Move with a white piece!\n");
			continue;
		}
		else if(whoseTurn == BLACKMOVE && board[startY][startX] > 6)
		{
			printf("It's black's turn! Move with a black piece!\n");
			continue;
		}
		AllowedMoves(whoseTurn, startY, startX, board[startY][startX]);

		printf("Enter the location you want to move the piece to (e.g. A1): ");
		scanf(" %c%d", &endCol, &endRow);
		endCol = toupper(endCol);
		endX = endCol - 'A';
		endY = SIZE - endRow;
		
		// Check if move is legal
		
		if(legalMoves[endY][endX] != 1)
			printf("That is not a legal move. Please try again.\n");
			
		UpdatePrev();
		board[endY][endX] = board[startY][startX];
		board[startY][startX] = EMPTYSPACE;
		
		IsCheck();
		AllowedMoves(whoseTurn, startY, startX, board[startY][startX]);
		
		
		if(whoseTurn == 0 && whiteCheck == 0)
				validMove = 1;
		else if(whoseTurn == 1 && blackCheck == 0)
			validMove = 1;
		else
		{	
			printf("You would still be in check! Try again.\n");
			RevertCurrent();
		}
	}
	
	// Check print
	if(whiteCheck == 1)
	{
		printf("The white king is in check!\n");
	}
	else if(blackCheck == 1)
	{
		printf("The black king is in check!\n");
	}
	
	
	madeMoves[whoseTurn][moveNumber] = startY*SIZE + startX;
	madeMoves[whoseTurn][moveNumber+1] = endY*SIZE + endX;
	moveNumber ++;
	
	if(whoseTurn == 1)
		whoseTurn = 0;
	else
		whoseTurn++;
}

int AllowedMoves(int whoChecks, int Y, int X, int pieceType)
{
	int i, j;

	// Set legalMoves array to all 0s
	for(i = 0; i < SIZE; i++)
	{
		for(j = 0; j < SIZE; j++)
			legalMoves[i][j] = 0;
	}

	switch(pieceType)
	{
		case BLACKPAWN:
		{
			if((Y > 0) && (board[Y+1][X] == EMPTYSPACE)) // Move forward one space
				legalMoves[Y+1][X] = 1;
			if((Y == 1) && (board[Y+1][X] == EMPTYSPACE) && (board[Y+2][X] == EMPTYSPACE)) // Move forward two spaces
				legalMoves[Y+2][X] = 1;
			if((X > 0) && (Y > 0) && (board[Y+1][X-1] > 6)) // Capture diagonal left
				legalMoves[Y+1][X-1] = 1;
			if((X < 7) && (Y > 0) && (board[Y+1][X+1] > 6)) // Capture diagonal right
				legalMoves[Y+1][X+1] = 1;
			break;
		}
		case WHITEPAWN:
		{
			if((Y < 7) && (board[Y-1][X] == EMPTYSPACE)) // Move forward one space
				legalMoves[Y-1][X] = 1;
			if((Y == 6) && (board[Y-1][X] == EMPTYSPACE) && (board[Y-2][X] == EMPTYSPACE)) // Move forward two spaces
				legalMoves[Y-2][X] = 1;
			if((X > 0) && (Y < 7) && (board[Y-1][X-1] > 0) && (board[Y-1][X-1] < 7)) // Capture diagonal left
				legalMoves[Y-1][X-1] = 1;
			if((X < 7) && (Y < 7) && (board[Y-1][X+1] > 0) && (board[Y-1][X+1] < 7)) // Capture diagonal right
				legalMoves[Y-1][X+1] = 1;
			break;
		}
		case BLACKROOK:
		case WHITEROOK:
		{
			for(i = Y-1; i >= 0; i--) // Capture vertically down
			{
				if(board[i][X] == EMPTYSPACE)
					legalMoves[i][X] = 1;
				else if((whoseTurn == 0) && (board[i][X] < 7))
				{
					legalMoves[i][X] = 1;
					break;
				}
				else if((whoseTurn == 1) && (board[i][X] > 6))
				{
					legalMoves[i][X] = 1;
					break;
				}
				else
					break;
			}
			for(i = Y+1; i < SIZE; i++) // Capture vertically up
			{
				if(board[i][X] == EMPTYSPACE)
					legalMoves[i][X] = 1;
				else if((whoseTurn == 0) && (board[i][X] < 7))
				{
					legalMoves[i][X] = 1;
					break;
				}
				else if((whoseTurn == 1) && (board[i][X] > 6))
				{
					legalMoves[i][X] = 1;
					break;
				}
				else
					break;
			}
			for(i = X+1; i < SIZE; i++) // Capture horizontally right
			{
				if(board[Y][i] == EMPTYSPACE)
					legalMoves[Y][i] = 1;
				else if((whoseTurn == 0) && (board[Y][i] < 7))
				{
					legalMoves[Y][i] = 1;
					break;
				}
				else if((whoseTurn == 1) && (board[Y][i] > 6))
				{
					legalMoves[Y][i] = 1;
					break;
				}
				else
					break;
			}
			for(i = X-1; i >= 0; i--) // Capture horizontally left
			{
				if(board[Y][i] == EMPTYSPACE)
					legalMoves[Y][i] = 1;
				else if((whoseTurn == 0) && (board[Y][i] < 7))
				{
					legalMoves[Y][i] = 1;
					break;
				}
				else if((whoseTurn == 1) && (board[Y][i] > 6))
				{
					legalMoves[Y][i] = 1;
					break;
				}
				else
					break;
			}
			break;
		}
		case BLACKBISHOP:
		case WHITEBISHOP:
		{
			for(i = 1; (Y+i < SIZE) && (X+i < SIZE); i++) // Capture diagonally up and right
			{
				if(board[Y+i][X+i] == EMPTYSPACE)
					legalMoves[Y+i][X+i] = 1;
				else if((whoseTurn == 1) && (board[Y+i][X+i] > 6))
				{
					legalMoves[Y+i][X+i] = 1;
					break;
				}
				else if((whoseTurn == 0) && (board[Y+i][X+i] < 7))
				{
					legalMoves[Y+i][X+i] = 1;
					break;
				}
				else
					break;
			}
			for(i = 1; (Y+i < SIZE) && (X-i >= 0); i++) // Capture diagonally up and left
			{
				if(board[Y+i][X-i] == EMPTYSPACE)
					legalMoves[Y+i][X-i] = 1;
				else if((whoseTurn == 1) && (board[Y+i][X-i] > 6))
				{
					legalMoves[Y+i][X-i] = 1;
					break;
				}
				else if((whoseTurn == 0) && (board[Y+i][X-i] < 7))
				{
					legalMoves[Y+i][X-i] = 1;
					break;
				}
				else
					break;
			}
			for(i = 1; (Y-i >= 0) && (X+i < SIZE); i++) // Capture diagonally down and right
			{
				if(board[Y-i][X+i] == EMPTYSPACE)
					legalMoves[Y-i][X+i] = 1;
				else if((whoseTurn == 1) && (board[Y-i][X+i] > 6))
				{
					legalMoves[Y-i][X+i] = 1;
					break;
				}
				else if((whoseTurn == 0) && (board[Y-i][X+i] < 7))
				{
					legalMoves[Y-i][X+i] = 1;
					break;
				}
				else
					break;
			}
			for(i = 1; (Y-i >= 0) && (X-i >= 0); i++) // Capture diagonally down and left
			{
				if(board[Y-i][X-i] == EMPTYSPACE)
					legalMoves[Y-i][X-i] = 1;
				else if((whoseTurn == 1) && (board[Y-i][X-i] > 6))
				{
					legalMoves[Y-i][X-i] = 1;
					break;
				}
				else if((whoseTurn == 0) && (board[Y-i][X-i] < 7))
				{
					legalMoves[Y-i][X-i] = 1;
					break;
				}
				else
					break;
			}
			break;
		}
		case BLACKKNIGHT:
		case WHITEKNIGHT:
		{
			if((X > 0) && (X < 7) && (Y > 1) && (board[Y-2][X-1] == EMPTYSPACE)) // Capture "L" shape up and left
				legalMoves[Y-2][X-1] = 1;
			else if((whoseTurn == 1) && (board[Y-2][X-1] > 6))
				legalMoves[Y-2][X-1] = 1;
			else if((whoseTurn == 0) && (board[Y-2][X-1] < 7))
				legalMoves[Y-2][X-1] = 1;
			if((X > 0) && (X < 7) && (Y > 1) && (board[Y-2][X+1] == EMPTYSPACE)) // Capture "L" shape up and right
				legalMoves[Y-2][X+1] = 1;
			else if((whoseTurn == 1) && (board[Y-2][X+1] > 6))
				legalMoves[Y-2][X+1] = 1;
			else if((whoseTurn == 0) && (board[Y-2][X+1] < 7))
				legalMoves[Y-2][X+1] = 1;
			if((X > 1) && (Y > 0) && (Y < 7) && (board[Y-1][X-2] == EMPTYSPACE)) // Capture "L" shape left and up
				legalMoves[Y-1][X-2] = 1;
			else if((whoseTurn == 1) && (board[Y-1][X-2] > 6))
				legalMoves[Y-1][X-2] = 1;
			else if((whoseTurn == 0) && (board[Y-1][X-2] < 7))
				legalMoves[Y-1][X-2] = 1;
			if((X > 1) && (Y > 0) && (Y < 7) && (board[Y+1][X-2] == EMPTYSPACE)) // Capture "L" shape left and down
				legalMoves[Y+1][X-2] = 1;
			else if((whoseTurn == 1) && (board[Y+1][X-2] > 6))
				legalMoves[Y+1][X-2] = 1;
			else if((whoseTurn == 0) && (board[Y+1][X-2] < 7))
				legalMoves[Y+1][X-2] = 1;
			if((X < 6) && (Y > 1) && (board[Y-2][X+1] == EMPTYSPACE)) 			 // Capture "L" shape down and right
				legalMoves[Y-2][X+1] = 1;
			else if((whoseTurn == 1) && (board[Y-2][X+1] > 6))
				legalMoves[Y-2][X+1] = 1;
			else if((whoseTurn == 0) && (board[Y-2][X+1] < 7))
				legalMoves[Y-2][X+1] = 1;
			if((X > 0) && (Y > 1) && (board[Y-2][X-1] == EMPTYSPACE)) 			 // Capture "L" shape down and left ?
				legalMoves[Y-2][X-1] = 1;
			else if((whoseTurn == 1) && (board[Y-2][X-1] > 6))
				legalMoves[Y-2][X-1] = 1;
			else if((whoseTurn == 0) && (board[Y-2][X-1] < 7))
				legalMoves[Y-2][X-1] = 1;
			if((X < 6) && (Y > 0) && (Y < 7) && (board[Y-1][X+2] == EMPTYSPACE)) // Capture "L" shape right and up
				legalMoves[Y-1][X+2] = 1;
			else if((whoseTurn == 1) && (board[Y-1][X+2] > 6))
				legalMoves[Y-1][X+2] = 1;
			else if((whoseTurn == 0) && (board[Y-1][X+2] < 7))
				legalMoves[Y-1][X+2] = 1;
			if((X < 6) && (Y > 0) && (Y < 7) && (board[Y+1][X+2] == EMPTYSPACE)) // Capture "L" shape right and down
				legalMoves[Y+1][X+2] = 1;
			else if((whoseTurn == 1) && (board[Y+1][X+2] > 6))
				legalMoves[Y+1][X+2] = 1;
			else if((whoseTurn == 0) && (board[Y+1][X+2] < 7))
				legalMoves[Y+1][X+2] = 1;
			break;
		}
		case BLACKKING:
		case WHITEKING:
		{
			if((Y > 0) && (board[Y-1][X] == EMPTYSPACE)) // Capture up
				legalMoves[Y-1][X] = 1;
			else if((whoseTurn == 1) && (board[Y-1][X] > 6))
				legalMoves[Y-1][X] = 1;
			else if((whoseTurn == 0) && (board[Y-1][X] < 7))
				legalMoves[Y-1][X] = 1;
			if((Y < 7) && (board[Y+1][X] == EMPTYSPACE)) // Capture down
				legalMoves[Y+1][X] = 1;
			else if((whoseTurn == 1) && (board[Y+1][X] > 6))
				legalMoves[Y+1][X] = 1;
			else if((whoseTurn == 0) && (board[Y+1][X] < 7))
				legalMoves[Y+1][X] = 1;
			if((X > 0) && (board[Y][X-1] == EMPTYSPACE)) // Capture left
				legalMoves[Y][X-1] = 1;
			else if((whoseTurn == 1) && (board[Y][X-1] > 6))
				legalMoves[Y][X-1] = 1;
			else if((whoseTurn == 0) && (board[Y][X-1] < 7))
				legalMoves[Y][X-1] = 1;
			if((X < 7) && (board[Y][X+1] == EMPTYSPACE)) // Capture right
				legalMoves[Y][X+1] = 1;
			else if((whoseTurn == 1) && (board[Y][X+1] > 6))
				legalMoves[Y][X+1] = 1;
			else if((whoseTurn == 0) && (board[Y][X+1] < 7))
				legalMoves[Y][X+1] = 1;
			if((X > 0) && (Y > 0) && (board[Y-1][X-1] == EMPTYSPACE)) // Capture down and left
				legalMoves[Y-1][X-1] = 1;
			else if((whoseTurn == 1) && (board[Y-1][X-1] > 6))
				legalMoves[Y-1][X-1] = 1;
			else if((whoseTurn == 0) && (board[Y-1][X-1] < 7))
				legalMoves[Y-1][X-1] = 1;
			if((X > 0) && (Y < 7) && (board[Y+1][X-1] == EMPTYSPACE)) // capture up and left
				legalMoves[Y+1][X-1] = 1;
			else if((whoseTurn == 1) && (board[Y+1][X-1] > 6))
				legalMoves[Y+1][X-1] = 1;
			else if((whoseTurn == 0) && (board[Y+1][X-1] < 7))
				legalMoves[Y+1][X-1] = 1;
			if((X < 7) && (Y > 0) && (board[Y-1][X+1] == EMPTYSPACE)) // Capture down and right
				legalMoves[Y-1][X+1] = 1;
			else if((whoseTurn == 1) && (board[Y-1][X+1] > 6))
				legalMoves[Y-1][X+1] = 1;
			else if((whoseTurn == 0) && (board[Y-1][X+1] < 7))
				legalMoves[Y-1][X+1] = 1;
			if((X < 7) && (Y < 7) && (board[Y+1][X+1] == EMPTYSPACE)) // capture up and right
				legalMoves[Y+1][X+1] = 1;
			else if((whoseTurn == 1) && (board[Y+1][X+1] > 6))
				legalMoves[Y+1][X+1] = 1;
			else if((whoseTurn == 0) && (board[Y+1][X+1] < 7))
				legalMoves[Y+1][X+1] = 1;
			break;
		}
		case BLACKQUEEN:
		case WHITEQUEEN:
		{
			// Capture vertically
			for(i = Y+1; i < SIZE; i++) // Capture vertically down
			{
				if(board[i][X] == EMPTYSPACE)
					legalMoves[i][X] = 1;
				else if((whoseTurn == 0) && (board[i][X] < 7))
				{
					legalMoves[i][X] = 1;
					break;
				}
				else if((whoseTurn == 1) && (board[i][X] > 6))
				{
					legalMoves[i][X] = 1;
					break;
				}
				else
					break;
			}
			for(i = Y-1; i >= 0; i--) // Capture vertically up
			{
				if(board[i][X] == EMPTYSPACE)
					legalMoves[i][X] = 1;
				else if((whoseTurn == 0) && (board[i][X] < 7))
				{
					legalMoves[i][X] = 1;
					break;
				}
				else if((whoseTurn == 1) && (board[i][X] > 6))
				{
					legalMoves[i][X] = 1;
					break;
				}
				else
					break;
			}
		
			// Capture horizontally
			for(i = X+1; i < SIZE; i++) // Capture horizontally right
			{
				if(board[Y][i] == EMPTYSPACE)
					legalMoves[Y][i] = 1;
				else if((whoseTurn == 0) && (board[Y][i] < 7))
				{
					legalMoves[Y][i] = 1;
					break;
				}
				else if((whoseTurn == 1) && (board[Y][i] > 6))
				{
					legalMoves[Y][i] = 1;
					break;
				}
				else
					break;
			}
			for(i = X-1; i >= 0; i--) // Capture horizontally left
			{
				if(board[Y][i] == EMPTYSPACE)
					legalMoves[Y][i] = 1;
				else if((whoseTurn == 0) && (board[Y][i] < 7))
				{
					legalMoves[Y][i] = 1;
					break;
				}
				else if((whoseTurn == 1) && (board[Y][i] > 6))
				{
					legalMoves[Y][i] = 1;
					break;
				}
				else
					break;
			}
		
			// Capture diagonally
			for(i = 1; (Y+i < SIZE) && (X+i < SIZE); i++) // Capture diagonally up and right
			{
				if(board[Y+i][X+i] == EMPTYSPACE)
					legalMoves[Y+i][X+i] = 1;
				else if((whoseTurn == 1) && (board[Y+i][X+i] > 6))
				{
					legalMoves[Y+i][X+i] = 1;
					break;
				}
				else if((whoseTurn == 0) && (board[Y+i][X+i] < 7))
				{
					legalMoves[Y+i][X+i] = 1;
					break;
				}
				else
					break;
			}
			for(i = 1; (Y+i < SIZE) && (X-i >= 0); i++) // Capture diagonally up and left
			{
				if(board[Y+i][X-i] == EMPTYSPACE)
					legalMoves[Y+i][X-i] = 1;
				else if((whoseTurn == 1) && (board[Y+i][X-i] > 6))
				{
					legalMoves[Y+i][X-i] = 1;
					break;
				}
				else if((whoseTurn == 0) && (board[Y+i][X-i] < 7))
				{
					legalMoves[Y+i][X-i] = 1;
					break;
				}
				else
					break;
			}
			for(i = 1; (Y-i >= 0) && (X+i < SIZE); i++) // Capture diagonally down and right
			{
				if(board[Y-i][X+i] == EMPTYSPACE)
					legalMoves[Y-i][X+i] = 1;
				else if((whoseTurn == 1) && (board[Y-i][X+i] > 6))
				{
					legalMoves[Y-i][X+i] = 1;
					break;
				}
				else if((whoseTurn == 0) && (board[Y-i][X+i] < 7))
				{
					legalMoves[Y-i][X+i] = 1;
					break;
				}
				else
					break;
			}
			for(i = 1; (Y-i >= 0) && (X-i >= 0); i++) // Capture diagonally down and left
			{
				if(board[Y-i][X-i] == EMPTYSPACE)
					legalMoves[Y-i][X-i] = 1;
				else if((whoseTurn == 1) && (board[Y-i][X-i] > 6))
				{
					legalMoves[Y-i][X-i] = 1;
					break;
				}
				else if((whoseTurn == 0) && (board[Y-i][X-i] < 7))
				{
					legalMoves[Y-i][X-i] = 1;
					break;
				}
				else
					break;
			}
		}
	}

	for(i = 0; i < SIZE; i++)
		{
			for(j = 0; j < SIZE; j++)
			{
				if(legalMoves[i][j] == 1)
					return 1;
			}
		}
	return 0;
}

void PrintLegalMoves(void)
{
	int i, j;
	
	for(i = 0; i < SIZE; i++)
	{
		for(j = 0; j < SIZE; j++)
		{
			printf("%d ", legalMoves[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
}

void IsCheck(void)
{
	int i, j;
	int wKingX, wKingY, bKingX, bKingY;
	int wTTemp;
	
	whiteCheck = 0;
	blackCheck = 0;
	
	// search for kings
	for(i = 0; i < SIZE; i++)
	{
		for(j = 0; j < SIZE; j++)
		{
			if(board[i][j] == WHITEKING)
			{
				wKingX = j;
				wKingY = i;
				// printf("White king at %d %d\n", j + 1, SIZE - i);
			}
			else if(board[i][j] == BLACKKING)
			{
				bKingX = j;
				bKingY = i;
				// printf("Black king at %d %d\n", j + 1, SIZE - i);
			}
		}
	}
	
	for(i = 0; i < SIZE; i++)
	{
		for(j = 0; j < SIZE; j++)
		{
			// sets correct colour to attack
			wTTemp = whoseTurn;
			if(board[j][i] < 7 && board[j][i] > 0)
			{
				whoseTurn = BLACKMOVE;
				AllowedMoves(BLACKMOVE, j, i, board[j][i]);
			}
			else if(board[j][i] > 0)
			{
				whoseTurn = WHITEMOVE;
				AllowedMoves(WHITEMOVE, j, i, board[j][i]);
			}
			else
				continue;
			whoseTurn = wTTemp;
				
			
			// checks if piece can take king
			
			if(legalMoves[wKingY][wKingX] == 1)
			{
				whiteCheck = 1;
				printf("White in check from %d %d!\n", i+1,SIZE - j);
			}
			else if(legalMoves[bKingY][bKingX] == 1)
			{
				blackCheck = 1;
				printf("Black in check from %d %d!\n", i+1, SIZE - j);
			}
		}
	}
	
}

void UpdatePrev(void)
{
	int i, j;
	
	for(i = 0; i < SIZE; i++)
	{
		for(j = 0; j < SIZE; j++)
		{
			prevBoard[i][j] = board[i][j];
		}
	}
}
void RevertCurrent(void)
{
	int i, j;
	
	for(i = 0; i < SIZE; i++)
	{
		for(j = 0; j < SIZE; j++)
		{
			board[i][j] = prevBoard[i][j];
		}
	}
}

void KingDeadCheck(void)
{
	int i, j;
	whiteKingAlive = 0;
	blackKingAlive = 0;
	
	for(i = 0; i < SIZE; i++)
	{
		for(j = 0; j < SIZE; j++)
		{
			if(board[i][j] == WHITEKING)
				whiteKingAlive = 1;
			else if(board[i][j] == BLACKKING)
				blackKingAlive = 1;
		}
	}
}
