#ifndef BFN_H
#define BFN_H
#include <ncurses.h>
#include <stdlib.h>
#include <math.h>
#include <menu.h>
#include <panel.h>
#include <string.h>
#include <form.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#include <unistd.h>
//default ncurses window values
//easily changed
//if changed my affect how some print statements display
#define DEFAULTWINX 65
#define DEFAULTWINY 25
#define OFFSETWINX 5
#define OFFSETWINY 5
//Header file to make organization easier
//and to allow for uses of multiple structs
//without clutter

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

//boardslot setup
typedef struct bslot
{
	int index;
	char letter;
	struct bslot* next;
	struct bslot* prev;
}boardslot;

//adj list struct
typedef struct adlist
{
	boardslot *start;
}adjlist;

//graph based struct for board
typedef struct graph
{
	adjlist** array;
	char* letters;
	int verts;
}board;


//print main menu art and vague instructions
void printmainmenu(WINDOW*);
//help page choice function
void help();
//NxN boggle function
void nboggle();
//actually playing the game function
void playboggle(int val);
///search functions
char* path_to_string(board* B,int  path[]);
void print_paths(board* B,int src, int dest, dictrie *root);
void print_all_pathsU(board* B,int u, int d, int visited[],int path[], int path_index, dictrie *root);
//panels creation function
void makepanel(panelnames** pn,char* name);
//resize function for main menu
void resizemenu(panelnames* pn,MENU* m);
//generic resize handler
void resizefixer(panelnames* pn);
//trie making function based on custom struct
dictrie* maketrie(char * word,dictrie* root);
//function to find words within trie on
//character by character basis
int wordsearch(int* path, dictrie* root, board* B, int length);
//function t create adj lists for entire board
board* makeboard(char boardletters[], int Bsize);
//used within make board to ease readability and code structure
void createBnode(adjlist* list, char letter, int I);
//psudeo rng function using rand and time seeding
int randx(int x);
//function to decide which "side" of the die is used 
//for the requested number of dice
void makedice(int input, char usedletters[]);
//file pointer declaration
FILE* f;
#endif