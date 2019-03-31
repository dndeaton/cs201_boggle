#include <ncurses.h>
#include <stdlib.h>
#include <menu.h>
#include <panel.h>
#include <stdbool.h>

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

//trie node setup
typedef struct tnode
{
	char letter;
	bool isend;
	struct tnode* children[26];
}dictrie;



//print main menu art and vague instructions
void printmainmenu(WINDOW*);
//help page choice function
void help();
//4x4 boggle function
void smallboggle();
//5x5 boggle function
void bigboggle();
//NxN boggle function
void nboggle();

void makepanel(panelnames** pn,char* name);

void resizemenu(panelnames* pn,MENU* m);
void resizefixer(panelnames* pn);
dictrie* maketrie(char * word,dictrie* root);
