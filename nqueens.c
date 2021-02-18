#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

#include "list.h"
#include "board.h"

list_t openList_p;
list_t closedList_p;

// Shows nodes from initial to solution
void showSolution(Node goal)
{
	int i = 0;

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
		child_p;

	while (listCount(&openList_p))
	{
		/* While items are on the open list */
		/* Get the first item on the open list */
		cur_node = popFirst(&openList_p);

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
				child_p = getChildBoard(cur_node, i);

				if (child_p != NULL)
				{
					// it's a valid child!
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
		child_p;

	while (listCount(&openList_p))
	{
		/* While items are on the open list */
		/* Get the first item on the open list */
		cur_node = popFirst(&openList_p);

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

				child_p = getChildBoard(cur_node, i);

				if (child_p != NULL)
				{
					// it's a valid child!

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

void UCS(void)
{
	Item *cur_node, *child_p, *temp;

	while (listCount(&openList_p))
	{
		/* Gets the best node on list */
		cur_node = popBest(&openList_p);		

		if (evaluateBoard(cur_node) == 0.0)
		{
			showSolution(cur_node);
			return;
		}
		/* if not already visited */
		if (!onList(&closedList_p, cur_node->board))
		{
			
			addLast(&closedList_p, cur_node);
			for (int i = 0; i < MAX_BOARD; i++)
			{
				child_p = getChildBoard(cur_node, i);
				if (child_p != NULL)
				{
					temp = onList(&openList_p, child_p->board);
					if (temp)
					{
						/* Compare score with node on the list to keep the best one */
						if (temp->f > child_p->f)
						{
							delList(&openList_p, temp);
							addLast(&openList_p, child_p);
						}
					}
					if (!onList(&closedList_p, child_p->board))
					{
						addLast(&openList_p, child_p);
					}
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
	printBoard(initial_state);

	printf("\nSearching ...\n");

	initial_state->f = 0.0;
	addFirst(&openList_p, initial_state);

	printList(openList_p);
	// printList(closedList_p);

	clock_t start, end;
	double cpu_time_used;

	start = clock();

	bfs();
	// dfs();
	// UCS();
	end = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	printf("Finished in %e seconds!\n", cpu_time_used);

	/* clean lists */
	cleanupList(&openList_p);
	cleanupList(&closedList_p);

	return 0;
}