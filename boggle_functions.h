#include <ncurses.h>
#include <stdlib.h>
#include <menu.h>
#include <panel.h>

#define DEFAULTWINX 65
#define DEFAULTWINY 25
#define OFFSETWINX 5
#define OFFSETWINY 5
//make panel organization easier

typedef struct pan
{
	char* name;
	PANEL* p;
}panelnames;



//misc functions header
void printboggle(WINDOW*);

void help();

void smallboggle();

void makepanel(panelnames** pn,char* name);