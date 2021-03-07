#include <stdio.h>
#include <string.h>
#define MAX_WORD_LENGTH 30
int main(int argc,char *argv[]) //this is the main function that has 2 arguments passed through it which are given by the user
{
	if(argc<2)
	{
		printf("invalid.");
		return 1;
	}
	int count=0;
	char word[MAX_WORD_LENGTH];
	FILE *fp;
	fp=fopen(argv[1],"r");
	if(fp==NULL) //This checks if the file exists
	{
		printf("No File Found.\n");
		return 1;
	}
	while(fscanf(fp,"%s",word)>0) //This is a while loop to incrament count until the file is empty
	{
		count++;
	}
	printf("The file has %d words\n",count);
	fclose(fp);
}
