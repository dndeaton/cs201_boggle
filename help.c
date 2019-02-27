#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <curses.h>
#include <menu.h>

/*Help/Rules file*/
 
/*
To Do

>Make outermost "function" to call
>>>>While loop for ch!=backspace???
>make ^ make new window at same size as main menu window
>add text to say "press backspace at any time to return to main menu"
>Print out boggle rules
>is there a way to automate print out for my window size to reduce print lines?
*/

//Define backspace as a ch or what to make ref easier???

int main(void){
int keypress;
//Add Needed ncurses stuff to make window
while((keypress=getch())!=(int)KEY_BACKSPACE)
{
//Print out the stuff
}

}