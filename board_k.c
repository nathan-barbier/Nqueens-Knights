#include <stdio.h>
//#include <malloc.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include "board.h"

#include <string.h>

// Initialize a new Game for the nQueens problem: an empty board..
Node initGame()
{
	int i;
	Node node;

	char *initial = (char *)malloc(MAX_BOARD * sizeof(char));
	initial[0] = 1;
	for (int i = 1; i < MAX_BOARD; i++)
		initial[i] = 0;

	node = nodeAlloc();

	initBoard(node, initial);
	node->depth = 0;

	return node;
}

// print a board
void printBoard(Node node)
{
	assert(node);

	printf("\n");
	for (int j = 0; j < WH_BOARD; j++)
		if (j == 0)
			printf(" ___");
		else
			printf("____");
	printf("\n");
	for (int i = 0; i < MAX_BOARD; i++)
	{
		if (i % WH_BOARD == 0)
			printf("|");
		if (node->board[i] == 0)
			printf("   |");
		else
			printf("%2d |", node->board[i]);
		if (((i + 1) % WH_BOARD) == 0)
		{
			printf("\n");
			for (int j = 0; j < WH_BOARD; j++)
				if (j == 0)
					printf(" ___");
				else
					printf("____");
			printf("\n");
		}
	}
	printf("\n");
}

// initialize node's state from a given board
void initBoard(Node node, char *board)
{
	assert(node);

	node->size = MAX_BOARD;
	node->board = calloc(MAX_BOARD, sizeof(char));

	/* Copy board */

	for (int i =0; i < MAX_BOARD; i++)
	{
		node->board[i] = board[i];
	}
}

// Return 0 if all queens are placed. Positive otherwise
// Ie: nb queens that still need to be placed.
double evaluateBoard(Node node)
{
	int dist = MAX_BOARD;
	int i;
	char *board = node->board;
	char isKnight;

	i = 0;
	while (i < MAX_BOARD)
	{
		// On trouve la case où est notre cavalier
		if (board[i] == 1)
		{
			// printf("Cavalier case %d\n", i);
			dist = MAX_BOARD - i - 1;
			// printf(" -> dist = %d\n", dist);
			return dist;
		}
		i++;
	}

	return dist;
}

// Test if position pos is valid with respect to node's state
// nQueens -> not same row ; not same column ; not same diagonal
int isValidPosition(Node node, int pos)
{
	int ii = pos / WH_BOARD;
	int jj = pos % WH_BOARD;

	char *board = node->board;

	int valid = 0;

	for (int i = 0; i < WH_BOARD; i++)
	{
		for (int j = 0; j < WH_BOARD; j++)
		{
			if (board[i * WH_BOARD + j] == 1)
			{
				if ((ii - i) * (ii - i) + (jj - j) * (jj - j) == 5)
				{
					valid++;
				}

			}
		}
	}
	
	return valid;
}

// Return a new item where a new knight is added at position pos if possible. NULL if not valid
Node getChildBoard(Node node, int pos)
{

	Node child_p = NULL;

	if (isValidPosition(node, pos))
	{
		// printf("testvalid\n");
		/* allocate and init child node */
		child_p = nodeAlloc();

		char *initial = (char *)malloc(MAX_BOARD * sizeof(char));
		for (int i = 0; i < MAX_BOARD; i++)
		initial[i] = 0;

		initBoard(child_p, initial);

		/* Make move (On place une nouvelle reine)*/
		// Est ce qu'on doit vérifier avec evaluateBoard si les reines sont déjà placées ?
		child_p->board[pos] = 1;

		/* link child to parent for backtrack */
		child_p->parent = node;
		child_p->depth = (child_p->parent)->depth + 1;
		child_p->f = child_p->depth;
	}

	return child_p;
}
