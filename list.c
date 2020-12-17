#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "list.h"

/* Item Functions */

Node nodeAlloc()
{
	Node node;

	node = (Node)malloc(sizeof(Item));
	assert(node);

	node->parent = NULL;
	node->prev = NULL;
	node->next = NULL;
	node->f = node->g = node->h = (double)0.0;

	return node;
}

void freeItem(Node node)
{
	if (node && node->board)
		free(node->board);
	if (node)
		free(node);
}

void initList(list_t *list_p)
{
	assert(list_p);

	list_p->numElements = 0;
	list_p->first = NULL;
	list_p->last = NULL;
}

int listCount(list_t *list)
{
	return list->numElements;
}

//return an item with corresponding board , or null
Item *onList(list_t *list, char *board)
{
	int i;
	if (list->first)
	{
		Node node;

		node = list->first;
		while (node->next)
		{
			i = 0;
			while (node->board[i] == board[i] && i < node->size)
			{
				i++;
			}
			if (i == node->size - 1) return node;
			
			node = node->next;
		}
	}

	return NULL;
}

// return and remove first item
Node popFirst(list_t *list) //
{
	assert(list);

	Node item = NULL;

	item = list->first;
	delList(list, list->first);

	return item;
}

// return and remove last item
Node popLast(list_t *list) //
{
	assert(list);

	Node item = NULL;

	item = list->last;
	delList(list, list->last);

	return item;
}

// remove a node from list
void delList(list_t *list, Item *node)
{
	// if(node==NULL){
	//     return;
	// }

	if (node == (list->first))
	{							  //si le node à supprimmer est le 1er el de liste
		list->first = node->next; //faire pointer le 1er el de la liste sur le suivant
		//(node->next)->prev=node->prev; //fait pointer le precedent du nouveau 1er el de la liste sur NULL
	}
	else if (node == (list->last))
	{							 //si le node à supprimmer est le dernier el de liste
		list->last = node->prev; //faire pointer le dernier el de la liste sur le precedent
		//(node->prev)->next=node->next; //fait pointer le suivant du nouveau 1er el de la liste sur NULL
	}
	if (node->prev != NULL)
	{
		(node->prev)->next = node->next;
	}
	if (node->next)
	{
		(node->next)->prev = node->prev;
	}
	//faire que le node pointe sur rien
	node->next = NULL;
	node->prev = NULL;
	//decrementer le nbr d'el de la liste
	(list->numElements)--;
}

// return and remove best item with minimal f value
Node popBest(list_t *list) // and remove the best board from the list.
{
	Node item = NULL;
	return item;
}

// add item in top
void addFirst(list_t *list, Node node) // add in head
{
	//cas liste vide
	if ((list->first) == NULL)
	{
		//mettre le node en seul el de la liste
		list->first = node;
		list->last = node;
	}

	//cas liste non vide
	else
	{
		(list->first)->prev = node; //mettre le node devant la liste
		node->next = list->first;	//mettre le suivant de node sur le 1er el de la liste
		list->first = node;			//mettre node en 1er el de la liste
	}
	(list->numElements)++;
}

// add item in queue
void addLast(list_t *list, Item *node) // add in tail
{
	//cas liste vide
	if ((list->first) == NULL)
	{
		list->first = node;
		list->last = node;
	}

	//si liste non vide
	else
	{
		(list->last)->next = node;
		node->prev = list->last;
		list->last = node;
	}

	(list->numElements)++;
}

void cleanupList(list_t *list)
{
	if (list->first)
	{
		Node item = list->first;
		Node tmp;

		while (item->next)
		{
			tmp = item->next;
			delList(list, item);
			freeItem(item);
			item = tmp;
		}
	}

	list->first = NULL;
	list->last = NULL;
	list->numElements = 0;
}

void printList(list_t list)
{
	Node item = list.first;
	while (item)
	{
		printf("%.2f [%s] - ", item->f, item->board);
		item = item->next;
	}
	printf(" (nb_items: %d)\n", list.numElements);
}

// TEST LIST
/* 
int main()
{
	printf("Test\n");
	Node item;
	char str[3];

	list_t openList;

	initList(&openList);

	for (int i = 0; i < 10; i++)
	{
		item = nodeAlloc();
		item->f = i;
		sprintf(str, "%2d", i);
		item->board = strdup(str);
		addLast(&openList, item);
		
	}

	for (int i = 20; i < 25; i++)
	{
		item = nodeAlloc();
		item->f = i;
		sprintf(str, "%2d", i);
		item->board = strdup(str);
		addFirst(&openList, item);
		
	}

	printList(openList);
	printf("\n");

	Node node = popBest(&openList);
	// // // printf("best node = %.2f\n", node->f);
	// // // printList(openList);
	// // // printf("\n");

	strcpy(str, "23");
	node = onList(&openList, str);
	if (node)
		printf("found %s: %.2f!\n", str, node->f);
	printList(openList);
	printf("\n");

	node = popFirst(&openList);

	item = nodeAlloc();
	item->f = 50;
	sprintf(str, "50");
	item->board = strdup(str);
	addLast(&openList, item);

	node = popFirst(&openList);
	if (node)
		printf("first: %.2f\n", node->f);
	printList(openList);
	printf("\n");

	node = popLast(&openList);
	if (node)
		printf("last: %.2f\n", node->f);
	printList(openList);
	printf("\n");

	printf("clean\n");
	cleanupList(&openList);
	printList(openList);
	printf("\n");

	return 0;
} */
