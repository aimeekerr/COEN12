/* Aimee Kerr
 * Lab 4
 * n in runtime stands for lp->count and assume "Runtime" means "Worst Big-O runtime".
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "list.h"
#include "set.h"
struct set{ //This initializes the set.
	int count;
	int length;
	LIST **lists;
	int (*compare)();
	unsigned (*hash)();
};
SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)()) //This function creates the set by allocating its memmory and giving it all the correct values and then it returns it's pointer. Runtime: O(n).
{
	int i;
	SET *sp;
	sp=malloc(sizeof(SET));
	assert(sp!=NULL);
	sp->count=0;
	sp->length=maxElts/20;
	sp->compare=compare;
	sp->hash=hash;
	sp->lists=malloc(sizeof(LIST*)*sp->length);
	for(i=0;i<sp->length;i++)
	{
		sp->lists[i]=createList(sp->compare);
	}
	return sp;
}
void destroySet(SET *sp) //This function destroys the set after the program is over. Runtime: O(n).
{
	assert(sp!=NULL);
	int i;
	for(i=0;i<sp->length;i++)
	{
		assert(sp->lists[i]!=NULL);
		destroyList(sp->lists[i]);
	}
	free(sp->lists);
	free(sp);
	return;
}
int numElements(SET *sp) //This function returns the number of elements in the set. Runtime: O(1).
{
	assert(sp!=NULL);
	return sp->count;
}
void addElement(SET *sp, void *elt) //This function adds the given element by hashing to the correct list pointer in the set and then calling the addFirst function. Runtime: O(1).
{
	assert(sp!=NULL);
	int key;
	key=(((*sp->hash)(elt))%sp->length);
	if(findItem(sp->lists[key],elt)==NULL)
	{
		addLast(sp->lists[key],elt);
		sp->count++;
	}
	return;
}
void removeElement(SET *sp, void *elt) //This function removes the given element from the list by hashing to the correct list pointer in the set and then calling the removeItem function. Runtime: O(1).
{
	assert(sp!=NULL);
	int key;
	key=(((*sp->hash)(elt))%sp->length);
	if(findItem(sp->lists[key],elt))
	{
		removeItem(sp->lists[key],elt);
		sp->count--;
	}
	return;
}
void *findElement(SET *sp, void *elt) //This function finds the given item by hashing to the correct list and then calling to the findItem function and returning what it finds. Runtime: O(n).
{
	assert(sp!=NULL);
	int key;
	key=((*sp->hash)(elt)%sp->length);
	return findItem(sp->lists[key],elt);
}
void *getElements(SET *sp) //This function creates an array with all of the values in the set and then returns it. Runtime: O(n).
{
	assert(sp!=NULL);
	int i,j=0;
	void **array=malloc(sizeof(void*)*(sp->count));
	for(i=0;i<sp->length;i++)
	{
		memcpy(array+j,getItems(sp->lists[i]),sizeof(void*)*numItems(sp->lists[i]));
		j+=numItems(sp->lists[i]);
	}
	return array;
}
