#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h> //#include <malloc.h>

#include "list.h"
#include "board_k.h"

list_t openList_p;
list_t closedList_p;

void showSolution(Node goal)
{
	int i = 0,
		j;

	printf("\nSolution:");

	while (goal)
	{
		printBoard(goal);
		goal = goal->parent;
		i++;
	}

	printf("\nLength of the solution = %d\n", i - 1);
	printf("Size of open list = %d\n", openList_p.numElements);
	printf("Size of closed list = %d\n", closedList_p.numElements);
	return;
}

void bfs(void)
{
	Node cur_node,
		child_p,
		temp;
	int i;
	while (listCount(&openList_p))
	{
		/* While items are on the open list */
		/* Get the first item on the open list */
		// printf("inf\n");
		cur_node = popFirst(&openList_p);
		printf("Test : %d  %f\n", listCount(&openList_p), evaluateBoard( cur_node ));
		printBoard(cur_node);

		/* Add it to the "visited" list */
		addLast(&closedList_p, cur_node);

		/* Do we have a solution? */
		if (evaluateBoard(cur_node) == 0.0)
		{
			showSolution(cur_node);
			return;
		}

		else
		{

			/* Enumerate adjacent states */
			for (int i = 0; i < MAX_BOARD; i++)
			{
				// printf("loop1\n");
				child_p = getChildBoard(cur_node, i);

				if (child_p != NULL)
				{
					// it's a valid child!
					// printBoard(child_p);

					/* Ignore this child if already visited */
					if (!onList(&closedList_p, child_p->board))
					{
						addLast(&openList_p, child_p);
					}
					/* Add child node to openList */
				}
			}
		}
	}

	return;
}

void dfs(void)
{
	Node cur_node,
		child_p,
		temp;
	int i;
	while (listCount(&openList_p))
	{
		/* While items are on the open list */
		/* Get the first item on the open list */
		// printf("inf\n");
		cur_node = popFirst(&openList_p);
		printf("Test : %d  %f\n", listCount(&openList_p), evaluateBoard( cur_node ));
		// printBoard(cur_node);

		/* Add it to the "visited" list */
		addLast(&closedList_p, cur_node);

		/* Do we have a solution? */
		if (evaluateBoard(cur_node) == 0.0)
		{
			showSolution(cur_node);
			return;
		}

		else
		{

			/* Enumerate adjacent states */
			for (int i = 0; i < MAX_BOARD; i++)
			{
				// printf("loop1\n");
				child_p = getChildBoard(cur_node, i);

				if (child_p != NULL)
				{
					// it's a valid child!
					// printBoard(child_p);

					/* Ignore this child if already visited */
					if (!onList(&closedList_p, child_p->board))
					{
						addFirst(&openList_p, child_p);
					}
					/* Add child node to openList */
				}
			}
		}
	}
}

int main()
{
	/* init lists */
	initList(&openList_p);
	initList(&closedList_p);

	// printList(openList_p);

	printf("\nInitial:");
	Node initial_state = initGame();
	printf("Init board : board = %s\n", initial_state->board);
	printBoard(initial_state);

	printf("\nSearching ...\n");

	addLast(&openList_p, initial_state);

	printList(openList_p);
	// printList(closedList_p);

	// bfs();
	dfs();
	printf("Finished!\n");

	/* clean lists */
	cleanupList(&openList_p);
	cleanupList(&closedList_p);

	return 0;
}