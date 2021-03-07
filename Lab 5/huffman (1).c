/*Aimee Kerr
 * Lab 5
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#define END 256
#include "pack.h"
#include "pqueue.h"
struct node *nodes[END+1];
static struct node *mknode(int data, struct node* left, struct node* right);
static int compare();
static int compare(struct node* left, struct node* right)
{
	if(left->count==right->count)
	{
		return 0;
	}
	else if(left->count<right->count)
	{
		return -1;
	}
	else
	{
		return 1;
	}
}
int depth(int c);
int main(int argc,char *argv[])
{
	int counts[END+1];
	int i;
	for(i=0;i<END+1;i++) //This initializes the array of counts and array of nodes with NULL/0 values.
	{
		nodes[i]=NULL;
		counts[i]=0;
	}
	char c;
	int numnodes=0;
	if(argc<2) //This checks to make sure a file was given.
	{
		printf("Invalid.\n");
		return 1;
	}
	FILE *fp;
	fp=fopen(argv[1],"r");
	if(fp==NULL) //This checks to make sure the file given is not NULL.
	{
		printf("No file found.\n");
		return 1;
	}
	c=getc(fp);
	while(c!=EOF) //This adds the occurance of each character into the counts array.
	{
		counts[(int)c]++;
		c=getc(fp);
	}
	if(c==EOF) //This makes sure that the end of the array is 0.
	{
		counts[END]=0;
	}
	struct node *np;
	PQ *pq;
	pq=createQueue(compare);
	nodes[END]=mknode(0,NULL,NULL);
	addEntry(pq,nodes[END]);
	for(i=0;i<END+1;i++) //This creates the priority queue with the values from the counts array.
	{
		if(counts[i]>0)
		{
			nodes[i]=mknode(counts[i],NULL,NULL);
			addEntry(pq,nodes[i]);
			numnodes++;
		}
	}
	while(numEntries(pq)>1) //This creates the actual tree using the values from the priority queue.
	{
		struct node *np1;
		struct node *np2;
		np1=removeEntry(pq);
		np2=removeEntry(pq);
		np=mknode((np1->count+np2->count),np1,np2);
		addEntry(pq,np);
	}
	for(i=0;i<END+1;i++) //This prints the information that is asked for in the lab manual.
	{
		if(nodes[i]>0)
		{
			if(isprint(i)>0)
			{
				printf("Character '%c': %d x %d = %d\n",i,counts[i],depth(i),counts[i]*depth(i));
			}
			else
			{
				printf("Character %c: %d x %d = %d\n",i,counts[i],depth(i),counts[i]*depth(i));
			}
		}
	}
	pack(argv[1],argv[2],nodes); //This sends the information to the pack function which will compress the data.
}
static struct node *mknode(int data, struct node* left, struct node* right) //This function creates the tree.
{
	struct node *np;
	np=malloc(sizeof(struct node));
	np->count=data;
	np->parent=NULL;
	if(left!=NULL)
	{
		left->parent=np;
	}
	if(right!=NULL)
	{
		right->parent=np;
	}
	return np;
}
int depth(int c) //This function finds the depth of the given character in the tree.
{
	struct node *p;
	p=nodes[c];
	int dep=0;
	while(p!=NULL)
	{
		p=p->parent;
		dep++;
	}
	return dep-1;
}
