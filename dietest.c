#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <curses.h>
#include "bigdice.h"
//HEADER SHIT I FORGET
;int randx(int x);
;int main(void)
{


    int side, i;
    srand(time(NULL));  // Seed ONCE based on time





char letters[25]={0};
int test[6]={0};
//initscr();//ncurses start
    for(i=0; i<25; ++i) // generate letters to be used from each die
    {
    	
        side = randx(6);
        // test[side]+=1;
        // printf("%d side ------ %d \n", side, i);
		letters[i]=die[i][side];
    }
for(i=0; i<25;++i)
{
	printf("%c",letters[i] );//change to put in ncurse display?
	
}

for(i=0; i<25;++i)
{
	letters[i];

}



//printf("%c \n", die[0][side]);

//printf("%d, %d, %d, %d, %d, %d \n", test[0], test[1], test[2], test[3], test[4], test[5]);

};

int randx(int x)
{
int dummy=rand()%5;
for(int j = 0; j<dummy; j++)
    	{
    		rand();
    	}
int num=rand()%x;
return num;
}