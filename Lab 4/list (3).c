/* Aimee Kerr
 * Lab 4
 * n in runtime stands for lp->count
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "list.h"
typedef struct node{ //This initializes the linked list.
	void *data;
	struct node *next;
	struct node *prev;
}NODE;
typedef struct list{ //This initializes the node that points to the head of the list.
	int count;
	struct node *head;
	int (*compare)();
}LIST;
LIST *createList(int (*compare)()) //This function creates the list with all the correct values and then returns a pointer to it. The runtime of this function is O(1).
{
	LIST *lp;
	NODE *dummy=malloc(sizeof(NODE));
	lp=malloc(sizeof(LIST));
	assert(lp!=NULL);
	lp->head=dummy;
	lp->count=0;
	lp->compare=compare;
	assert(lp->head!=NULL);
	dummy->prev=lp->head;
	dummy->next=lp->head;
	return lp;
}
void destroyList(LIST *lp) //This function destorys the list once the program is over by freeing everything. The runtime of this function is O(n).
{
	struct node *np,*next;
	assert(lp!=NULL);
	np=lp->head;
	do
	{
		next=np->next;
		free(np);
		np=next;
	}while(np!=lp->head);
	free(lp);
	return;
}
int numItems(LIST *lp) //This function returns the number of items in the list. The runtime of this function is O(1).
{
	return lp->count;
}
void addFirst(LIST *lp, void *item) //This function adds the given item to the front of the list (after the dummy node). The runtime of this function is O(1).
{
	NODE *p;
	p=malloc(sizeof(NODE));
	p->data=item;
	lp->head->next->prev=p;
	p->next=lp->head->next;
	lp->head->next=p;
	p->prev=lp->head;
	lp->count++;
	return;
}
void addLast(LIST *lp, void *item) //This function adds the given item to the end of the list. The runtime on this function is O(1).
{
	NODE *p;
	p=malloc(sizeof(NODE));
	p->data=item;
	lp->head->prev->next=p;
	p->prev=lp->head->prev;
	p->next=lp->head;
	lp->head->prev=p;
	lp->count++;
	return;
}
void *removeFirst(LIST *lp) //This function removes the first item (after the dummy node) from the list and returns its data. The runtime of this function O(1).
{
	assert(lp!=NULL);
	assert(lp!=0);
	NODE *p;
	p=lp->head->next;
	void *item=p->data;
	p->next->prev=lp->head;
	lp->head->next=p->next;
	free(p);
	lp->count--;
	return item;
}
void *removeLast(LIST *lp) //This function removes the last item from the list and returns its data. The runtime of this function is O(1).
{
	assert(lp!=NULL);
	assert(lp->count!=0);
	NODE *p;
	p=lp->head->prev;
	void *item=p->data;
	p->prev->next=lp->head;
	lp->head->prev=p->prev;
	free(p);
	lp->count--;
	return item;
}
void *getFirst(LIST *lp) //This function returns the data of the first element in the list. The runtime of this function is O(1).
{
	assert(lp!=NULL);
	assert(lp->count!=0);
	NODE *p;
	p=lp->head->next;
	return p->data;
}
void *getLast(LIST *lp) //This function returns the data of the last element in the list. The runtime of this function is O(1).
{
	assert(lp!=NULL);
	assert(lp->count!=0);
	NODE *p;
	p=lp->head->prev;
	return p->data;
}
void removeItem(LIST *lp, void *item) //This function removes the item with the matching data that is given. The runtime of this function is O(n).
{
	assert(lp!=NULL);
	assert(lp->compare!=NULL);
	NODE *p;
	p=lp->head->next;
	while(p!=lp->head)
	{
		if((*lp->compare)(item,p->data)==0)
		{
			p->prev->next=p->next;
			p->next->prev=p->prev;
			lp->count--;
			free(p);
			return;
		}
		p=p->next;
	}
	return;
}
void *findItem(LIST *lp, void *item) //This function finda the location of the item with the matching data that is given and returns it. The runtime of this function is O(n).
{
	assert(lp!=NULL);
	assert(lp->compare!=NULL);
	NODE *p;
	p=lp->head->next;
	while(p!=lp->head)
	{
		if((*lp->compare)(item,p->data)==0)
		{
			return p->data;
		}
		p=p->next;
	}
	return NULL;
}
void *getItems(LIST *lp) //This function creates an array of pointers to the data in the list and returns the array. The runtime of this function is O(n).
{
	int i=0;
	void **array=malloc(sizeof(void*)*(lp->count));
	NODE *p;
	p=lp->head->next;
	while(p!=lp->head)
	{
		array[i]=p->data;
		p=p->next;
		i++;
	}
	return array;
}
