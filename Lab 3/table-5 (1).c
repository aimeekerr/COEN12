/*Aimee Kerr
 *Lab 3 - Generic
 *Note: in runtime, n=sp->length.
 */ 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "set.h"
typedef struct set{ //this initializes the set
	int count;
	int length;
	void **data;
	char *flags;
	int (*compare)();
	unsigned (*hash)();
}SET;
SET *createSet(int maxElts, int (*compare)(),unsigned (*hash)()) //this creates a set and allocates all the memory for each element inside the set and then returns a pointer for it. Runtime: worst case: O(n) expected: O(1).
{
	int i;
	SET *sp;
	sp=malloc(sizeof(SET));
	assert(sp!=NULL);
	sp->data=malloc(sizeof(void *)*maxElts);
	sp->count=0;
	sp->length=maxElts;
	sp->compare=compare;
	sp->hash=hash;
	sp->flags=malloc(sizeof(char)*maxElts);
	assert(sp->flags!=NULL);
	for(i=0;i<sp->length;i++) //this fills all the slots in the flag array with "E" which stands for empty
	{
		sp->flags[i]='E';
	}
	return sp;
}
static int search(SET *sp, void *element,bool *x) //this function searches through the hash table and finds the index of the open slot and returns it OR returns the index of the element it matches. It also changes the bool value to true if it finds it. Runtime: worst case: O(n)  expected: O(1). 
{
	int key;
	int i;
	int si;
	int check=-1;
	key=((*sp->hash)(element))%sp->length;
	for(i=0;i<sp->length;i++)
	{
		si=(key+i)%sp->length;
		if(sp->flags[si]=='E')
		{
			*x=false;
			if(check!=-1)
			{
				return check;
			}
			else
			{
				return si;
			}
		}
		if(sp->flags[si]=='D')
		{
			if(check==-1)
			{
				check=si;
			}
		}
		if(sp->flags[si]=='F')
		{
			if((*sp->compare)(sp->data[si],element)==0)
			{
				*x=true;
				return si;
			}
		}
	}
	return -1;
}
void destroySet(SET *sp) //this function frees all the memory from the program. Runtime: expected and worst case: O(1).
{
	free(sp->data);
	free(sp->flags);
	free(sp);
	return;
}
int numElements(SET *sp) //this function checks if the set is empty and if it isn't, returns the number of elements. Runtime: expected and worst case: O(1).
{
	assert(sp!=NULL);
	return sp->count;
}
void addElement(SET *sp, void *elt) //this function adds the given element into the set. Runtime: worst case: O(n) Expected: O(1).
{
	bool x=false;
	int index;
	index=search(sp,elt,&x);
	if(x==false)
	{
		sp->data[index]=elt;
		sp->flags[index]='F';
		sp->count++;
	}
	return;
}
void removeElement(SET *sp, void *elt) //this function removes the given element from the set. Runtime: worst case: O(n) expected: O(1).
{
	bool x=false;
	int index;
	index=search(sp,elt,&x);
	if(x==true)
	{
		sp->flags[index]='D';
		sp->count--;
	}
	return;
}
void *findElement(SET *sp, void *elt) //this function finds the give element and returns its index OR NULL if it isn't found. Runtime: worst case: O(n) expected: O(1).
{
	bool x=false;
	int index;
	index=search(sp,elt,&x);
	if(x==true)
	{
		return sp->data[index];
	}
	else
	{
		return NULL;
	}
}
void *getElements(SET *sp) //this function creates a copy of the elements in the given set. Runtime: worst case: O(n) expected: O(1).
{
	int i;
	int counter=0;
	void **copy;
	copy=malloc(sizeof(void*)*sp->count);
	for(i=0;i<sp->length;i++)
	{
		if(sp->flags[i]=='F')
		{
			copy[counter]=sp->data[i];
			counter++;
		}
	}
	return copy;
}
