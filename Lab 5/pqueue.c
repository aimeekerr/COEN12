/*Aimee Kerr
 * Lab 5
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "pqueue.h"
#define l(x) (x*2)+1
#define r(x) (x*2)+2
typedef struct pqueue{
	int count;
	int length;
	int (*compare)();
	void **array;	
}PQ;
PQ *createQueue(int (*compare)())
{
	PQ *pq;
	pq=malloc(sizeof(PQ));
	assert(pq!=NULL);
	pq->count=0;
	pq->length=10;
	pq->compare=compare;
	pq->array=malloc(sizeof(void*)*10);
	return pq;
}
void destroyQueue(PQ *pq)
{
	assert(pq!=NULL);
	free(pq->array);
	free(pq);	
}
int numEntries(PQ *pq)
{
	return pq->count;
}
void addEntry(PQ *pq, void *entry)
{
	assert(pq!=NULL);
	int parent=((pq->count-1)/2);
	int child=pq->count;
	void *x;
	if(pq->count==pq->length)
	{
		pq->array=realloc(pq->array,(sizeof(void*)*(pq->length*2)));
		pq->length=(pq->length*2);
	}
	pq->array[pq->count]=entry;
	while(parent>=0 && (*pq->compare)(pq->array[child],pq->array[parent])<0)
	{
		x=pq->array[child];
		pq->array[child]=pq->array[parent];
		pq->array[parent]=x;
		child=parent;
		parent=(parent-1)/2;
	}
	pq->count++;
	return;
}
void *removeEntry(PQ *pq)
{
	assert(pq!=NULL);
	assert(pq->count>0);
	int index=0;
	int child;
	void *x=pq->array[pq->count-1];
	void *value=pq->array[0];
	pq->count--;
	while(l(index)<pq->count)
	{
		child=l(index);
		if(r(index)<pq->count)
		{
			if((*pq->compare)(pq->array[l(index)],pq->array[r(index)])>0)
			{
				child=r(index);
			}
		}
		if((*pq->compare)(x,pq->array[child])>0)
		{
			pq->array[index]=pq->array[child];
			index=child;
		}
		else
		{
			break;
		}
	}
	pq->array[index]=x;
	return value;
}
