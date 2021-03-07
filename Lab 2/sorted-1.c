#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "set.h"
typedef struct set{ //this initializes the structure
	int count;
	int length;
	char **data;
}SET;
SET *createSet(int maxElts) //this function recieves the max elements, creates the set, and then returns it's pointer
{
	SET *sp;
	sp=malloc(sizeof(SET));
	sp->data=malloc(sizeof(char *)*maxElts);
	sp->count=0;
	sp->length=maxElts;
	return sp;
}
static int search(SET *sp, char *element,bool *y) //this function binary searches through the list and returns the index of the found word or -1 if it isn't found
{
	int high=sp->count-1;
	int low=0,mid=0;
	while(low<=high)
	{
		mid=((low+high)/2);
		if(strcmp(sp->data[mid],element)==0)
		{
			*y=true;
			return mid;
		}
		if(strcmp(sp->data[mid],element)<0)
		{
			low=mid+1;
		}
		else
		{
			high=mid-1;
		}
	}
	*y=false;
	return low;
}
void destroySet(SET *sp)  //this function removes the set and frees all the pointers after the program is done
{
	int i;
	for(i=0;i<sp->count;i++)
	{
		free(sp->data[i]);
	}
	free(sp->data);
	free(sp);
	return;
}
int numElements(SET *sp) //this function checks if the list is empty and returns the numbers of elements in the list
{
	assert(sp!=NULL);
	return sp->count;
}
void addElement(SET *sp, char *elt)  //this function adds an element to the list and it doesn't return anything because it is a void function
{
	bool y=false;
	int check;
	char *dup;
	int i;
	dup=strdup(elt);
	if(sp->count==sp->length)
	{
		return;
	}
	check=search(sp,elt,&y);
	if(y==true)
	{
		return;
	}
	else
	{
		for(i=sp->count;i>check;i--)
		{
			sp->data[i]=sp->data[i-1];
		}
		sp->data[check]=dup;
		sp->count++;
		return;
	}
}
void removeElement(SET *sp, char *elt) //this function removes an element from the list and doesn't return anything because it is a void function
{
	bool y=false;
	int i;
	int check;
	check=search(sp,elt,&y);
	if(y==false)
	{
		return;
	}
	else
	{
		free(sp->data[check]);
		for(i=check;i<sp->count-1;i++)
		{
			sp->data[i]=sp->data[i+1];
		}
		sp->count--;
		return;
	}
}
char *findElement(SET *sp, char *elt) //this function finds a given elements index and then returns it or NULL if it is not found
{
	bool y=false;
	int check;
	check=search(sp,elt,&y);
	if(y==false)
		return NULL;
	else
		return sp->data[check];
}
char **getElements(SET *sp) //this function makes a copy of the set sp and returns it
{
	char **copy;
	copy=malloc(sizeof(char*)*sp->count);
	memcpy(copy,sp->data,sizeof(char*)*sp->count);
	return copy;
}
