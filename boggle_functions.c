#include "boggle_functions.h"

//comment




typedef struct pan panelnames;




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


void help()
{
panelnames* help=malloc(sizeof(panelnames));
makepanel(&help,"help");
top_panel(help->p);
update_panels();
doupdate();
int currenty=0;
int currentx=0;
int key;
nodelay(stdscr, TRUE);
while((key=getch())!=(int)KEY_BACKSPACE)
		{
getmaxyx(stdscr,currenty,currentx);
			if(key==(int) KEY_RESIZE)
			{
			while (currenty<(DEFAULTWINY+OFFSETWINY+5) || currentx<(DEFAULTWINX+OFFSETWINX+5) )//+5 for visual buffer
				{
			mvprintw(0,0,"Please resize window to be larger for best game experience");
			getmaxyx(stdscr,currenty,currentx);
			refresh();
				}
			 clear();
			 del_panel(help->p);
			 makepanel(&help,"help");
			//refresh();
			}
		wbkgd(panel_window(help->p),COLOR_PAIR(1));
		mvwprintw(panel_window(help->p),2,2,"TEST");
		update_panels();
		doupdate();
		refresh();
		wrefresh(panel_window(help->p));

		}

del_panel(help->p);
}




//pass windowfrom, name, 
void makepanel(panelnames** pn,char* name)
{
	WINDOW* window = newwin(DEFAULTWINY, DEFAULTWINX,OFFSETWINY, OFFSETWINX);
	panelnames* temp=*pn;
	temp->name=name;
	temp->p=new_panel(window);
	*pn=temp;
	//printf("called\n");





}

