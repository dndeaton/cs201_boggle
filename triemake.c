#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <curses.h>
#include <menu.h>
#include <panel.h>
#include "bigdice.h"
#include "boggle_functions.h"


int main(void)
{
FILE* fp =fopen("text.txt","r");
char c;
c=fgetc(fp);
dictrie* root=calloc(1,sizeof(dictrie));
root=maketrie("wrong",root);
printf("%c\n", root->children['w'-'a']->letter);
dictrie* temp=root;
temp=temp->children['w'-'a'];
temp=temp->children['r'-'a'];
printf("%c\n", temp->letter);
printf("%d\n",temp->isend );
temp=temp->children['o'-'a'];
printf("%c\n", temp->letter);
temp=temp->children['n'-'a'];
printf("%c\n", temp->letter);
temp=temp->children['g'-'a'];
printf("%c\n", temp->letter);
printf("%d\n",temp->isend );
// while(c!= EOF)
// 	{
// 		char temp[100]={0};
// 		int len=0;
// 		while(c!='\n'&& c!= EOF)
// 		{
// 			temp[len++]=c;
// 			//printf("%d\n", len );
// 			c = fgetc(fp);
		

// 		}

		
// 			c=fgetc(fp);
// 			// printf("notap\n");
// 			char* word=malloc(len*sizeof(char));
// 			for (int i = 0; i < len; ++i)
// 			{
// 				word[i]=temp[i];
// 			}
// 			printf("%s\n", word);//make trie here

		
// 	}
 fclose(fp);










//not printing read from list. prob cause is eof after not \n. add if con to fix?


}//end main



// void maketrie(dictrie* root, char* word)
// 	{
// 		for (int i = 0; word[i]!='' ; ++i)
// 		{
// 			/* code */
// 		}
// 	}
