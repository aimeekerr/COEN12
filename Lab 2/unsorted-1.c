#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "set.h"
typedef struct set{
	int count;
	int length;
	char **data;
}SET;
SET *createSet(int maxElts) //this function creates a set and returns the pointer to it
{
	SET *sp;
	sp=malloc(sizeof(SET));
	sp->data=malloc(sizeof(char *)*maxElts);
	sp->count=0;
	sp->length=maxElts;
	return sp;
}
static int search(SET *sp, char *element) //this function searches through the list and returns either the index of the element it is looking for or -1 if it is not found
{
	int check;
	int i;
	for(i=0;i<sp->count;i++)
	{
		check=strcmp(sp->data[i],element);
		if(check==0)
		{
			return i;
		}
	}
	return -1;
}
void destroySet(SET *sp) //this function frees everything after the program is over
{
	int i;
	assert(sp!=NULL);
	for(i=0;i<sp->count;i++)
	{
		free(sp->data[i]);
	}
	free(sp->data);
	free(sp);
	return;
}
int numElements(SET *sp) //this function returns the number of elements
{
	assert(sp!=NULL);
	return sp->count;
}
void addElement(SET *sp, char *elt) //this function adds an element to the list by moving the whole list to create room and then inserting the element and it doesn't return anything because it is a void function
{
	int check;
	char *dup;
	if(sp->count==sp->length)
	{
		return;
	}
	check=search(sp,elt);
	if(check!=-1)
	{
		return;
	}
	dup=strdup(elt);
	sp->data[sp->count]=dup;
	sp->count++;
	return;
}
void removeElement(SET *sp, char *elt) //this function removes an element from the list and then moves the list to close the gap
{
	int check;
	check=search(sp,elt);
	if(check==-1)
	{
		return;
	}
	else
	{
		free(sp->data[check]);
		sp->data[check]=sp->data[sp->count-1];
		sp->count--;
		return;
	}
}
char *findElement(SET *sp, char *elt)  //this function finds the element that is given and returns it or NULL if it is not found
{
	int check;
	check=search(sp,elt);
	if(check==-1)
		return NULL;
	else
		return sp->data[check];
}
char **getElements(SET *sp) //this function creates a copy of the set and returns it
{
	char **copy;
	copy=malloc(sizeof(char*)*sp->count);
	memcpy(copy,sp->data,sizeof(char*)*sp->count);
	return copy;
}
