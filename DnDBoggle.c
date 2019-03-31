/*
Digital recreation of Boggle
By David Deaton
2019
CS 201 Spring 2019
*/
//main file for portfolio
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <curses.h>
#include <menu.h>
#include <panel.h>
#include "boggle_functions.h"


/*
 *        ____                    __   
 *       / __ )____  ____ _____ _/ /__ 
 *      / __  / __ \/ __ `/ __ `/ / _ \
 *     / /_/ / /_/ / /_/ / /_/ / /  __/
 *    /_____/\____/\__, /\__, /_/\___/ 
 *                /____//____/         
 */	
int main(void)
{
//cleaing out words found from last time program was run
//to prevent issues
system("rm wordsfound.txt");
system("clear");

initscr();
start_color();
cbreak();
noecho();
keypad(stdscr, true);
curs_set(false);
refresh();
char* menuitems[5]={"Play","Rules/Help","Exit"};
init_pair(1,COLOR_RED,COLOR_WHITE);//Debugging color pair
//Making new colors because I can
 init_color(COLOR_MAGENTA, 200, 0, 200); 
 //repuposing magenta as purple because I won't use magenta as is
 //Default Background color pair to be used
init_pair(2,COLOR_WHITE,COLOR_MAGENTA);
refresh();
int key;
ITEM** mainmenu=(ITEM**) calloc(3+1,sizeof(ITEM*));//add one for memory reasons
for (int i=0; i<3;i++)
{
	mainmenu[i]=new_item(menuitems[i],"");//empty 2nd because no double printing
}
mainmenu[4]=(ITEM*)NULL;//filling 6th slot with nothing
//making window into panel
MENU* menuholder=(MENU*)NULL;
menuholder=new_menu((ITEM**)mainmenu);
panelnames* menu=malloc(sizeof(panelnames));
makepanel(&menu,"menu");
resizemenu(menu, menuholder);
refresh();
while((key=getch())!=(int)KEY_F(1))//F1  since need all letters open for typing answers eventually
{

switch(key)
	    {	case (int)KEY_DOWN:
	    	case (int)115://ascii "s"
		        menu_driver(menuholder, REQ_DOWN_ITEM);
			break;
			case (int)KEY_UP:
			case (int)119://ascii "w"
				menu_driver(menuholder, REQ_UP_ITEM);
				break;
			case (int)KEY_RESIZE://Resize Case
			resizemenu(menu, menuholder);
			break;
			case (int)10: //ascii enter
				 //Boggle option
				if (item_name(current_item(menuholder))==item_name(mainmenu[0]))
				{
					hide_panel(menu->p);
					nboggle();
					noecho();
					resizemenu(menu, menuholder);
					show_panel(menu->p);
					top_panel(menu->p);
				}
				// //Help case
				if (item_name(current_item(menuholder))==item_name(mainmenu[1]))
				{
					hide_panel(menu->p);
					help();
					resizemenu(menu, menuholder);
					show_panel(menu->p);
					top_panel(menu->p);
				}
				//Exit case
				if (item_name(current_item(menuholder))==item_name(mainmenu[3]))
				{
					//short wait before exit
					napms(1000);
					endwin();
					exit(1);
				}
				break;
		post_menu(menuholder);
		refresh();
		wrefresh(panel_window(menu->p));
		doupdate();
		}
post_menu(menuholder);


refresh();
wrefresh(panel_window(menu->p));



}
 refresh();
 endwin(); 
}	