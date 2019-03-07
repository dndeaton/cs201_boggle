#include "boggle_functions.h"

//comment




typedef struct pan panelnames;




void printmainmenu(WINDOW* menu)
{
mvwprintw(menu,3,1, "     ____                    __   ");
mvwprintw(menu,4,1, "    / __ )____  ____ _____ _/ /__ ");
mvwprintw(menu,5,1, "   / __  / __ \\/ __ `/ __ `/ / _ \\");
mvwprintw(menu,6,1, "  / /_/ / /_/ / /_/ / /_/ / /  __/");
mvwprintw(menu,7,1, " /_____/\\____/\\__, /\\__, /_/\\___/ ");
mvwprintw(menu,8,1, "             /____//____/         ");
mvwprintw(menu,9,4,"David Deaton 2019");

mvwprintw(menu,18,2,"Use w/s or up arrow/down arrow to hightlight an option"); 	
mvwprintw(menu,19,2,"Press enter to select it"); 
mvwprintw(menu,20,2,"Select Rules/Help for the full rules" );
mvwprintw(menu,21,2,"Press F1 at anytime to force close the game" );
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

void resizefixer(panelnames* pn)
{
	//unpost_menu(menuholder);//copied from DTC.c 150 
	int currenty=0;
	int currentx=0;
	clear();
	getmaxyx(stdscr,currenty,currentx);

		while (currenty<(DEFAULTWINY+OFFSETWINY+5) || currentx<(DEFAULTWINX+OFFSETWINX+5) )//+5 for visual buffer
		{
		mvprintw(0,0,"Please resize window to be larger for best game experience");
		getmaxyx(stdscr,currenty,currentx);
		refresh();
		}

	
	del_panel(pn->p);
	wbkgd(panel_window(pn->p),COLOR_PAIR(2));
	bkgd(COLOR_PAIR(2));	
	update_panels();
	doupdate();
	refresh();

	//Basic idea		
}

void resizemenu(panelnames* pn,MENU* m)
{

unpost_menu(m);
	resizefixer(pn);
WINDOW* menuwindow;
makepanel(&pn,pn->name);
menuwindow=derwin(panel_window(pn->p),10,20,12,3);//adjust last 2 for move menu around

wbkgd(panel_window(pn->p),COLOR_PAIR(2));
set_menu_fore(m,COLOR_PAIR(2));
set_menu_back(m,COLOR_PAIR(2));
set_menu_win(m,panel_window(pn->p));
set_menu_sub(m,menuwindow);//create padding
refresh();
box(panel_window(pn->p),0,0);
set_menu_mark(m,">");
printmainmenu(panel_window(pn->p));
post_menu(m);	
wrefresh(panel_window(pn->p));
update_panels();
doupdate();



	//extra stufff
}


dictrie* maketrie(char *word, dictrie* root)
{
	dictrie* temp=root;
	dictrie* trav=root;
	for (int i = 0; word[i]!='\0' ; ++i)
	{
	char x=word[i];
		if (trav->children[x-'a']==NULL)
		{
		dictrie* node=calloc(1,sizeof(dictrie));
		node->letter=x;
		if (word[i+1]=='\0')
		{
		node->isend=true;
		}
		else node->isend=false;
	
		trav->children[(int)(x-'a')]=node;
		trav=trav->children[(int)(x-'a')];
		}
		else if(trav->children[x-'a']!=NULL)
		{
		trav=trav->children[(int)(x-'a')];
		if (word[i+1]=='\0')
		{
		trav->isend=true;
		}
		else trav->isend=false;
		}
	
	
	//trav=trav->children[(int)(x-'a')];
	
	if (trav->isend==false)
	{
		printf("%c", trav->letter );
	}
	else printf("%c\n", trav->letter );

	}
	
	return temp;

}