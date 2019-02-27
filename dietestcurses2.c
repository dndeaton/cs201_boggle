#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <curses.h>
#include <menu.h>
#include "bigdice.h"
//HEADER SHIT I FORGET


/*
TO DO

>Resize fix thing
>figure out how to push down for ascii art
>Make template for "change window"
>
*/
;int main(void)
{

initscr();
start_color();
cbreak();
noecho();
keypad(stdscr, true);
refresh();//NEED THIS
char* menuitems[5]={"4x4","5x5","NxN","Rules/Help","Exit"};//4,5,n,help,exit
init_pair(1,COLOR_RED,COLOR_WHITE);
int h=25;//window size setup
int w=65;
int offsety=5;
int offsetx=5;
int currentx;
int currenty;

getmaxyx(stdscr,currenty,currentx);

while (currenty<(h+offsety+10) || currentx<(w+offsetx+10) )
{
	mvprintw(0,0,"Resize window");
	getmaxyx(stdscr,currenty,currentx);
	refresh();

}
napms(1000);//works but idk how to do it right
clear();



int ch;
ITEM** mainmenu=(ITEM**) calloc(5+1,sizeof(ITEM*));//add one for reasons...
for (int i=0; i<5;i++)
{
	mainmenu[i]=new_item(menuitems[i],"");//empty 2nd because no double printing
}
mainmenu[5]=(ITEM*)NULL;//filling 6th slot with nothing
WINDOW* menu;
MENU* menuholder=(MENU*)NULL;
menuholder=new_menu((ITEM**)mainmenu);

menu=newwin(h,w,offsety,offsetx);
WINDOW* menuwindow;
menuwindow=derwin(menu,10,20,10,2);//adjust last 2 for move menu around
wbkgd(menuwindow,COLOR_PAIR(1));
set_menu_win(menuholder,menu);
set_menu_sub(menuholder,menuwindow);//create padding
//wprintw(menu,"");
refresh();
box(menu,0,0);
set_menu_mark(menuholder,">");
mvwprintw(menu,17,2, "Use w/s or up arrow/down arrow to hightlight an option"); 
mvwprintw(menu,18,2,"Press enter to select it"); 
mvwprintw(menu,19,2,"Select Rules/Help for the full rules" );
mvwprintw(menu,20,2,"Press F1 at anytime to force close the game" );
post_menu(menuholder);	
wrefresh(menu);
refresh();
while((ch=getch())!=(int)KEY_F(1))//F1  since need all letters open for typing answers eventually
{

switch(ch)
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
			case (int)KEY_RESIZE://KINDA WORKS NEED HELP RE "PRINTING" MENU TO SCREEN
			unpost_menu(menuholder);
			clear();
			getmaxyx(stdscr,currenty,currentx);

			while (currenty<(h+offsety+10) || currentx<(w+offsetx+10) )
			{
			mvprintw(0,0,"Please resize window to be larger for best game experience");
			getmaxyx(stdscr,currenty,currentx);
			refresh();
			}
			napms(1000);//works but idk how to do it right
			//sleep(70000);
			menu=newwin(h,w,offsety,offsetx);
			WINDOW* menuwindow;
			menuwindow=derwin(menu,10,20,10,2);//adjust last 2 for move menu around
			wbkgd(menuwindow,COLOR_PAIR(1));
			set_menu_win(menuholder,menu);
			set_menu_sub(menuholder,menuwindow);//create padding
			//wprintw(menu,"");
			refresh();
			box(menu,0,0);
			set_menu_mark(menuholder,">");
			mvwprintw(menu,17,2, "Use w/s or up arrow/down arrow to hightlight an option"); 
			mvwprintw(menu,18,2,"Press enter to select it"); 
			mvwprintw(menu,19,2,"Select Rules/Help for the full rules" );
			mvwprintw(menu,20,2,"Press F1 at anytime to force close the game" );
			post_menu(menuholder);	
			wrefresh(menu);
			refresh();
			break;


			case (int)10: //ascii enter
				//4x4 case
				if (item_name(current_item(menuholder))==item_name(mainmenu[0]))
				{
					//RUN 4x4 CODE

				}
				//5x5 case
				if (item_name(current_item(menuholder))==item_name(mainmenu[1]))
				{
					//RUN 5x5 CODE

				}
				//NxN case
				if (item_name(current_item(menuholder))==item_name(mainmenu[2]))
				{
					//RUN NxN CODE

				}
				//Help case
				if (item_name(current_item(menuholder))==item_name(mainmenu[3]))
				{
					//NEW WINDOW TO BOGGLE RULES PRINTOUT
					//NEEDS RETURN TO MAIN MENU OPTION
				}

				//Exit case
				if (item_name(current_item(menuholder))==item_name(mainmenu[4]))
				{
					endwin();
					exit(1);

				}
				break;
		post_menu(menuholder);
		refresh();
		wrefresh(menu);

		}

	if (ch==122)//122 = ascii "z"
	{
		printw("z pressed");
	}

	if(ch == KEY_LEFT)
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
// do resize fnction




	