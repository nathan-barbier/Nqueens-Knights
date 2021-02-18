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
	Node node;

	char *initial = (char *)malloc(MAX_BOARD * sizeof(char));
	for (int i = 0; i < MAX_BOARD; i++)
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

	for (int i = 0; i < MAX_BOARD; i++)
	{
		node->board[i] = board[i];
	}
}

// Return 0 if all queens are placed. Positive otherwise
// Ie: nb queens that still need to be placed.
double evaluateBoard(Node node)
{
	int nb = WH_BOARD;
	int i;
	char *board = node->board;
	char isQueen;

	i = 0;
	while (i < MAX_BOARD && nb > 0)
	{
		isQueen = board[i];
		if (isQueen == 1)
			nb--;
		i++;
	}

	return nb;
}

// Test if position pos is valid with respect to node's state
// nQueens -> not same row ; not same column ; not same diagonal
int isValidPosition(Node node, int pos)
{
	int ii = pos / WH_BOARD;
	int jj = pos % WH_BOARD;

	char *board = node->board;

	// Test de la ligne
	for (int j = 0; j < WH_BOARD; j++)
	{
		if (board[ii * WH_BOARD + j] == 1)
			return 0;
	}

	// Test de la colonne
	for (int i = 0; i < WH_BOARD; i++)
	{
		if (board[i * WH_BOARD + jj] == 1)
			return 0;
	}

	// Test des diagonales
	for (int i = 0; i < WH_BOARD; i++)
	{
		for (int j = 0; j < WH_BOARD; j++)
		{
			if (abs(ii - i) == abs(jj - j) && board[i * WH_BOARD + j] == 1)
				return 0;
		}
	}
	return 1;
}

// Return a new item where a new queen is added at position pos if possible. NULL if not valid
Node getChildBoard(Node node, int pos)
{

	Node child_p = NULL;

	if (isValidPosition(node, pos))
	{
		/* allocate and init child node */
		child_p = nodeAlloc();
		initBoard(child_p, node->board);

		/* Make move (On place une nouvelle reine)*/

		child_p->board[pos] = 1;

		/* link child to parent for backtrack */
		child_p->parent = node;
		child_p->depth = (child_p->parent)->depth + 1;
		child_p->f = child_p->depth;
	}

	return child_p;
}
