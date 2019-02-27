/*
Digital recreation of Boggle
By David Deaton
2019
CS 201
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <curses.h>
#include <menu.h>
#include <panel.h>
#include "bigdice.h"
//#include "help.c" //Did I do this right????
//HEADER SHIT I FORGET


/*
 *        ____                    __   
 *       / __ )____  ____ _____ _/ /__ 
 *      / __  / __ \/ __ `/ __ `/ / _ \
 *     / /_/ / /_/ / /_/ / /_/ / /  __/
 *    /_____/\____/\__, /\__, /_/\___/ 
 *                /____//____/         
 */	
/*
TO DO

>fix exit case printout
>
>Make template for "change window"
>Make Help window
>Make algorithm based on / dic file
>>>Eliminate Proper nouns? per rules
>Colors for all windows
>>> Ubuntu purple and white works fine
>Make printboggle function work so it's not a mess when reprinting
*/
void printboggle(WINDOW* menu);
int main(void)
{

initscr();
start_color();
cbreak();
noecho();
keypad(stdscr, true);
refresh();//NEED THIS
char* menuitems[5]={"4x4","5x5","NxN","Rules/Help","Exit"};//4,5,n,help,exit
init_pair(1,COLOR_RED,COLOR_WHITE);//Debugging color pair
//Making new colors because I can
//WHY ARE NCURSES COLORS SO DULLED? This should be like neon pink?
 init_color(COLOR_MAGENTA, 200, 0, 200); //repuposing magenta as purple because I won't use magenta
    /* param 1     : color name
     * param 2, 3, 4 : rgb content min = 0, max = 1000 */
 //Default Backfround color pair to be used
init_pair(2,COLOR_WHITE,COLOR_MAGENTA);

//change terminal background idk how
//wbkgd(stdwin,COLOR_PAIR(2));
int h=25;//window size setup
int w=65;
int offsety=5;
int offsetx=5;
int currentx;
int currenty;
//Checking if window is big enough for game to function
getmaxyx(stdscr,currenty,currentx);
while (currenty<(h+offsety+5) || currentx<(w+offsetx+5) )//+5 for visual buffer
{
	mvprintw(0,0,"Please resize window to be larger for best game experience");
	getmaxyx(stdscr,currenty,currentx);
	refresh();
}
//napms(1000);//works but idk how to do it right
clear();

//checking supported colors 256
//printw("My terminal supports %d colors.\n", COLORS);

int key;
ITEM** mainmenu=(ITEM**) calloc(5+1,sizeof(ITEM*));//add one for reasons...
for (int i=0; i<5;i++)
{
	mainmenu[i]=new_item(menuitems[i],"");//empty 2nd because no double printing
}
mainmenu[5]=(ITEM*)NULL;//filling 6th slot with nothing
//making window and into panel
WINDOW* menu;

MENU* menuholder=(MENU*)NULL;

menuholder=new_menu((ITEM**)mainmenu);

menu=newwin(h,w,offsety,offsetx);


PANEL* Pmain=(PANEL*)NULL;
Pmain=new_panel(menu);



WINDOW* menuwindow;
wbkgd(menu,COLOR_PAIR(2));
set_menu_fore(menuholder,COLOR_PAIR(2));
set_menu_back(menuholder,COLOR_PAIR(2));
//wbkgd(menu,COLOR_PAIR(1));
menuwindow=derwin(menu,10,20,12,3);//adjust last 2 for move menu around
wbkgd(menuwindow,COLOR_PAIR(2));
set_menu_win(menuholder,menu);
set_menu_sub(menuholder,menuwindow);//create padding
//wprintw(menu,"");
refresh();
box(menu,0,0);
set_menu_mark(menuholder,">");
//Print ASCII Logo and creator name
printboggle(menu);
//Print minimum detail instructions on Main Menu
mvwprintw(menu,18,2,"Use w/s or up arrow/down arrow to hightlight an option"); 	
mvwprintw(menu,19,2,"Press enter to select it"); 
mvwprintw(menu,20,2,"Select Rules/Help for the full rules" );
mvwprintw(menu,21,2,"Press F1 at anytime to force close the game" );
post_menu(menuholder);	
wrefresh(menu);
refresh();
while((key=getch())!=(int)KEY_F(1))//F1  since need all letters open for typing answers eventually
{

switch(key)
	    {	case (int)KEY_DOWN:
	    	case (int)115://ascii "s"
		        menu_driver(menuholder, REQ_DOWN_ITEM);
		       //s printw("DOWN pressed");
				break;
			case (int)KEY_UP:
			case (int)119://ascii "w"
				menu_driver(menuholder, REQ_UP_ITEM);
				//printw("UP pressed");
				break;
			case (int)KEY_RESIZE://Working, I think, Resize Case
			unpost_menu(menuholder);
			clear();
			getmaxyx(stdscr,currenty,currentx);

			while (currenty<(h+offsety+5) || currentx<(w+offsetx+5) )//+5 for visual buffer
			{
			mvprintw(0,0,"Please resize window to be larger for best game experience");
			getmaxyx(stdscr,currenty,currentx);
			refresh();
			}
//printw("resized1\n");
			//napms(1000);//CAUSES DUMB LONG HANG TIME ON RESIZE AFTER CORRECT SIZE LIKE 15s long????
			menu=newwin(h,w,offsety,offsetx);
			WINDOW* menuwindow;
			wbkgd(menu,COLOR_PAIR(2));
			set_menu_fore(menuholder,COLOR_PAIR(2));
			set_menu_back(menuholder,COLOR_PAIR(2));
//printw("resized2\n");
			menuwindow=derwin(menu,10,20,12,2);//adjust last 2 for move menu around
			//wbkgd(menuwindow,COLOR_PAIR(1));
//printw("resized3\n");
			set_menu_win(menuholder,menu);
			set_menu_sub(menuholder,menuwindow);//create padding
			//wprintw(menu,"");
//printw("resized4\n");
			refresh();
			box(menu,0,0);
//printw("resized5\n");
			set_menu_mark(menuholder,">");
//Print ASCII Logo and creator name
printboggle(menu);
//Print minimum detail instructions on Main Menu
			mvwprintw(menu,18,2,"Use w/s or up arrow/down arrow to hightlight an option"); 	
			mvwprintw(menu,19,2,"Press enter to select it"); 
			mvwprintw(menu,20,2,"Select Rules/Help for the full rules" );
			mvwprintw(menu,21,2,"Press F1 at anytime to force close the game" );
//printw("resized6\n");
			post_menu(menuholder);	
			wrefresh(menu);
//printw("resized7\n");
			refresh();
			break;


			case (int)10: //ascii enter
				//printw("enter pressed");
				//4x4 case
				if (item_name(current_item(menuholder))==item_name(mainmenu[0]))
				{
					printw("4x4 selected");
				}
				//5x5 case
				if (item_name(current_item(menuholder))==item_name(mainmenu[1]))
				{
					printw("5x5 selected");

				}
				// //NxN case
				if (item_name(current_item(menuholder))==item_name(mainmenu[2]))
				{
					printw("NxN selected");

				}
				// //Help case
				if (item_name(current_item(menuholder))==item_name(mainmenu[3]))
				{
					//HELP ME JESUS

					while((key=getch())!=(int)KEY_BACKSPACE)
						{
						WINDOW* help;
					help=newwin(h,w,offsety,offsetx);
					PANEL* Phelp=(PANEL*)NULL;
					Phelp=new_panel(WINDOW *help);
					
					top_panel(P_help);
					update_panels();
					doupdate();
					mvwprintw(help,1,1, "TEST");
						}
					

					//printw("Rules/Help selected");
					//NEW WINDOW TO BOGGLE RULES PRINTOUT
					//NEEDS RETURN TO MAIN MENU OPTION
				}
				//Exit case
				if (item_name(current_item(menuholder))==item_name(mainmenu[4]))
				{
					printw("Exit selected");//Not printed???
					napms(2000);
					endwin();
					exit(1);
				}
				break;
		post_menu(menuholder);
		refresh();
		wrefresh(menu);

		}

	if (key==122)//122 = ascii "z"
	{
		printw("z pressed");
	}

	if(key == KEY_LEFT)
	{
        printw("Left arrow is pressed");
	}
	post_menu(menuholder);
	refresh();
	wrefresh(menu);




}


  

 refresh();
 endwin(); 
}

void printboggle(WINDOW* menu)
{
mvwprintw(menu,3,1, "     ____                    __   ");
mvwprintw(menu,4,1, "    / __ )____  ____ _____ _/ /__ ");
mvwprintw(menu,5,1, "   / __  / __ \\/ __ `/ __ `/ / _ \\");
mvwprintw(menu,6,1, "  / /_/ / /_/ / /_/ / /_/ / /  __/");
mvwprintw(menu,7,1, " /_____/\\____/\\__, /\\__, /_/\\___/ ");
mvwprintw(menu,8,1, "             /____//____/         ");
mvwprintw(menu,9,4,"David Deaton 2019");
}
// do resize fnction




	