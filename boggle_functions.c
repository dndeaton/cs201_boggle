#include "boggle_functions.h"
/*
Definition of all needed functions for DnDBoggle.c
*/
//definition of default boggle dice
char * die[]= {	"RIFOBX",
				"IFEHEY",
				"DENOWS",
				"UTOKND",
				"HMSRAO",
				"LUPETS",
				"ACITOA",
				"YLGKUE",
				"QBMJOA",
				"EHISPN",
				"VETIGN",
				"BALIYT",
				"EZAVND",
				"RALESC",
				"UWILRG",
				"PACEMD",
			   };
//defintion of used structs to make my life easier
typedef struct pan panelnames;
typedef struct tnode dictrie;
typedef struct bslot boardslot;
typedef struct graph board;



//quick way to call the needed printouts for the mainmenu 
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

//function to display the Rules/Help page within the game
void help()
{
panelnames* help=malloc(sizeof(panelnames));
makepanel(&help,"help");
//moving new window to the top of the stack of panels to be displayed
top_panel(help->p);
update_panels();
doupdate();
int currenty=0;
int currentx=0;
int key;
nodelay(stdscr, TRUE);

//commonly used while loop to handle ncurses resizing of windows
//not applied to all windows due to user input issues
while((key=getch())!=(int)KEY_BACKSPACE)
		{
getmaxyx(stdscr,currenty,currentx);
			if(key==(int) KEY_RESIZE)
			{
			while (currenty<(DEFAULTWINY+OFFSETWINY+5) || currentx<(DEFAULTWINX+OFFSETWINX+5) )//+5 for visual buffer
				{
			mvprintw(0,0,"Please resize window to be larger until menu appears and then close and restart the program");
			getmaxyx(stdscr,currenty,currentx);	
			refresh();
				}
			 clear();
			 del_panel(help->p);
			 makepanel(&help,"help");
			//refresh();
			}

		
		//adding a border to the ncurses window for style and reasdability
		box(panel_window(help->p),0,0);
		//Changing window to different colors
		wbkgd(panel_window(help->p),COLOR_PAIR(2));
		//Printing out all the rules for boggle. Short handed due to window size limitations
		mvwprintw(panel_window(help->p),1,30,"RULES:");
		mvwprintw(panel_window(help->p),2,2, "The goal of Boggle is to have the highest point total.");
		mvwprintw(panel_window(help->p),3,2, "To gain points, each player must create words from the");
		mvwprintw(panel_window(help->p),4,2, "shown grid of letters. The longer the word,");
		mvwprintw(panel_window(help->p),5,2, "the higher the point value of the word. words are");
		mvwprintw(panel_window(help->p),6,2, "created by using adjoining letters in any direction.");
		mvwprintw(panel_window(help->p),7,2, "The letters must be connected in the correct order");
		mvwprintw(panel_window(help->p),8,2, "to spell the resulting word correctly. Letters may join");
		mvwprintw(panel_window(help->p),9,2, "in any direction (including backwards) ie horizontally,");
		mvwprintw(panel_window(help->p),10,2,"vertically, or diagonally. You may NOT use the same");
		mvwprintw(panel_window(help->p),11,2,"letter space twice in a word. Any word found in an English");
		mvwprintw(panel_window(help->p),12,2,"dictionary is allowed, Except for proper nouns");
		mvwprintw(panel_window(help->p),13,2,"and words smaller than 3 letters. The game will start once");
		mvwprintw(panel_window(help->p),14,2,"a board size is chosen and the start option is selected.");
		mvwprintw(panel_window(help->p),15,2,"You should set a timer for the default 3 minutes or your");
		mvwprintw(panel_window(help->p),16,2,"prefered time. During that time find as many words as");
		mvwprintw(panel_window(help->p),17,2,"you can. Once time is up. The found words and their score");
		mvwprintw(panel_window(help->p),18,2,"will be printed to a local file 'foundwords.txt'. You should");
		mvwprintw(panel_window(help->p),19,2,"sum up your score from the file. 3 letter words are 1pt,");
		mvwprintw(panel_window(help->p),20,2,"4 are 1pt, 5 are 2pts, 6 are 3pts,7 are 4pts, 8+ are 11pts.");
		mvwprintw(panel_window(help->p),21,2,"Note: Board sizes above 23x23 will be solved, but will not");
		mvwprintw(panel_window(help->p),22,2,"display properly due to display limitations");
		mvwprintw(panel_window(help->p),23,2,"Press Backspace to return to the main menu");

// neccessary functions to display ncurses updates in window. Used often
		update_panels();
		doupdate();
		refresh();
		wrefresh(panel_window(help->p));

		}
//deleting panel when user presses backspace
del_panel(help->p);
}


//function to encapsulate all needed processes to play boggle
//not resizeable due to user input limitations
void nboggle()
{
/* messages to be appeared on the screen */
 char mesg[]="Enter a number for board size (must be > 3)";
 char mesg2[]="ie 5 for a 5x5 board: ";
char sizemesg[]="Max number of input digits is 10";
char sizemesg2[]="Max number is (2^31)-1";//put in readme
char fmesg[]="Invalid input press any key to return to main menu";
char tmesg[]="Board size selected press any key to proceed";
char str[15]={'\0'};
panelnames* nboggle=malloc(sizeof(panelnames));
makepanel(&nboggle,"nboggle");
nodelay(panel_window(nboggle->p), FALSE);//Needed to get user input
echo();//needed to show user what they're typing
top_panel(nboggle->p);
box(panel_window(nboggle->p),0,0);
wbkgd(panel_window(nboggle->p),COLOR_PAIR(2));
update_panels();
doupdate();
refresh();
wrefresh(panel_window(nboggle->p));
mvwprintw(panel_window(nboggle->p),20,2,"%s",sizemesg);
mvwprintw(panel_window(nboggle->p),21,2,"%s",sizemesg2);
mvwprintw(panel_window(nboggle->p),3,2,"%s",mesg);
mvwprintw(panel_window(nboggle->p),4,2,"%s",mesg2);


update_panels();
doupdate();
refresh();
wrefresh(panel_window(nboggle->p));
//getting user input for board size
wgetnstr(panel_window(nboggle->p),str, 10);
noecho();
//checking if input was an int and preform case if not
int val = (int) atoi(str);

//conditionals to check for valid user input
	if (val==0)
		{
		//printf("%lu ==0\n", val );
		wbkgd(panel_window(nboggle->p),COLOR_PAIR(1));
		mvwprintw(panel_window(nboggle->p),7,5,"%s",fmesg);
		update_panels();
		doupdate();
		refresh();
		wrefresh(panel_window(nboggle->p));
		getch();
		update_panels();
		doupdate();
		refresh();
		wrefresh(panel_window(nboggle->p));
		del_panel(nboggle->p);
		//return;
		}
		//val is a valid input but not greater than 4
	else if (val!=0 && (val<4))
		{
			//printf("%lu ==0 <4\n", val );
		wbkgd(panel_window(nboggle->p),COLOR_PAIR(1));
		mvwprintw(panel_window(nboggle->p),7,5,"%s",fmesg);

		update_panels();
		doupdate();
		refresh();
		wrefresh(panel_window(nboggle->p));
		getch();
		update_panels();
		doupdate();
		refresh();
		wrefresh(panel_window(nboggle->p));
		del_panel(nboggle->p);
		//return;
		}
		//val is a valid input
	else if (val!=0 && val>=4)//works for str like "e4" or "r", but not "4ee" or "5e3" due to atoi limitations
		{
		mvwprintw(panel_window(nboggle->p),9,5,"%s",tmesg);
		mvwprintw(panel_window(nboggle->p),7,5,"Board size entered =  %d  by  %d   ",val,val);
		mvwprintw(panel_window(nboggle->p),11,5,"press any key to return to continue");//placeholder
		update_panels();
		doupdate();
		refresh();
		wrefresh(panel_window(nboggle->p));
		getch();//waiting for user input to proceed, also reason this window can't be resized while active
		update_panels();
		doupdate();
		refresh();
		wrefresh(panel_window(nboggle->p));
		del_panel(nboggle->p);

		//calling actual functiont that runs the boggle game for cleanliness sake
		playboggle(val);

		}
		
}


//function that preforms all overarching processes to play boggle
void playboggle(int val)
{
	//making retrieval tree "trie" of dictionary file created by make file
	//is deleted upon game ending
FILE* fp =fopen("dict.txt","r");
char c;
c=fgetc(fp);
dictrie* root=calloc(1,sizeof(dictrie));
while(c!= EOF)
	{
		char temp[100]={0};
		int len=0;
		while(c!='\n'&& c!= EOF)
		{
			temp[len++]=c;
			//printf("%d\n", len );
			c = fgetc(fp);
		}
			c=fgetc(fp);
			// printf("notap\n");
			char* word=malloc(len*sizeof(char));
			for (int i = 0; i < len; ++i)
			{
				word[i]=temp[i];
			}
			// printf("%s\n", word);//make trie here
			//printf("B4maketrie\n");
			root=maketrie(word,root);
	}
 fclose(fp);
//End of trie creation


 //cleaning up files between games for error proofing
system("rm wordsfound.txt");
system("clear");
update_panels();
doupdate();
refresh();

//Creating a loading screen panel to inform the user that the board is being solved
//Only really seen when boards are above single 9x9
panelnames* Waitboggle=malloc(sizeof(panelnames));
makepanel(&Waitboggle,"Waitboggle");
nodelay(panel_window(Waitboggle->p), TRUE);//Needed to get user input
noecho();//needed to hide keypresses
top_panel(Waitboggle->p);
box(panel_window(Waitboggle->p),0,0);
wbkgd(panel_window(Waitboggle->p),COLOR_PAIR(2));
wrefresh(panel_window(Waitboggle->p));
update_panels();
doupdate();
refresh();
wrefresh(panel_window(Waitboggle->p));
mvwprintw(panel_window(Waitboggle->p),10,2,"Please wait while the board is solved");
mvwprintw(panel_window(Waitboggle->p),11,2,"You may begin playing after this step is completed");
mvwprintw(panel_window(Waitboggle->p),12,2,"Note: Larger boards may take a while so please");
mvwprintw(panel_window(Waitboggle->p),13,2,"do not exit, the solver is working");
update_panels();
doupdate();
refresh();
wrefresh(panel_window(Waitboggle->p));


//moving input board size to another variable fo acessability
int input=val;
int numdice=input*input;// 2894 hardware limit max
//Ran into hardware limitations above 2894, probably heap size issues
//not fixable on my end from what I tried
int Bsize=input;
//creating array of size equal to the used "dice" 
//inorder to pass into the dice randomization function
char usedletters[numdice];
makedice(input, usedletters);

//creating the adj lists for each node on the board
board *B= makeboard(usedletters, Bsize);

//opening the first file to print the found words into
f = fopen("wordsfounddupeunsorted.txt","w");
for (int i = 0; i < B->verts; ++i)
	{
	for (int j = 0; j < B->verts; ++j)
	{	//running word pathing function
	if(i!=j){print_paths(B,i,j, root);}
	}
	}
fclose(f);
//sorting the found words by length and then deleting any duplicates
//is slightly inefficient but I was unable to figure out how to have persistant
//values marking if a word was found with my method in time for the due date
system(" awk \'{print length(), " " $0;}\' wordsfounddupeunsorted.txt | sort -r -n | cut -d ' ' -f 2- >wordsfounddupe.txt");
system("awk '!x[$0]++' wordsfounddupe.txt > wordsfound.txt");
//deleting extra files since the user doesn't need them
//fails sometimes on board >=50x50 due to what I can only speculate is hardware limitations
//since I am unaware of how to fix it
system("rm wordsfounddupe.txt");
system("rm wordsfounddupeunsorted.txt");


update_panels();
doupdate();
refresh();
wrefresh(panel_window(Waitboggle->p));
//deleting the waiting screen and moving the user onto the Start screen for the game
del_panel(Waitboggle->p);

//Ready screen panel creation
//unable to be resized due to user input
panelnames* Ready=malloc(sizeof(panelnames));
clear();
makepanel(&Ready,"Ready");
nodelay(panel_window(Ready->p), FALSE);
top_panel(Ready->p);
wbkgd(panel_window(Ready->p),COLOR_PAIR(2));
box(panel_window(Ready->p),0,0);
update_panels();
doupdate();
//Ready notification messages
//I was unable to get a scalable timer working in ncurses so users must provide their own
//default is specified in Rules, but users can provide their own
mvwprintw(panel_window(Ready->p),12,25,"Solving complete");
mvwprintw(panel_window(Ready->p),13,1,"Press Enter to begin & Enter again when your timer has run out");
update_panels();
doupdate();
refresh();
wrefresh(panel_window(Ready->p));
//waiting for user to proceed to displaying boggle board
getch();
//clear();
del_panel(Ready->p);

//Make board display panel
panelnames* boggle=malloc(sizeof(panelnames));
clear();
makepanel(&boggle,"boggle");
top_panel(boggle->p);
box(panel_window(boggle->p),0,0);
wbkgd(panel_window(boggle->p),COLOR_PAIR(2));
update_panels();
doupdate();
refresh();
wrefresh(panel_window(boggle->p));
nodelay(panel_window(Ready->p), FALSE);

//Board display print code block
//works by checking if board side dimension has been reached
//moves to next line if so
//due to ncurses limitations
//display works improperly above 23x23 boards
int start_offset_r=1;
int start_offset_c=1;
int spacing_offset_r=1;
int spacing_offset_c=2;
int vert_bar_pos=1;
	
 //wmove(panel_window(boggle->p), 4, 4);
for(int r =0; r< Bsize*spacing_offset_r;r++)
{
	if(r%spacing_offset_r==0){
	for(int c=0; c< Bsize*spacing_offset_c;c++)
	{
		if(c%spacing_offset_c==0)
		{
			mvwprintw(panel_window(boggle->p),(r+start_offset_r),(c+start_offset_c),
			"%c",B->letters[(r/spacing_offset_r)*Bsize+c/spacing_offset_c]);
		}
		else if (c%spacing_offset_c==vert_bar_pos)
		{
			mvwprintw(panel_window(boggle->p),(r+start_offset_r),(c+start_offset_c),"|");
		}
	}
	}
}
update_panels();
doupdate();
refresh();
wrefresh(panel_window(boggle->p));
//waiting for user to press enter to say their timer is up
getch();
clear();
del_panel(boggle->p);


//creating game end message panel
//non resizable due to needing input to proceed
panelnames* Thanks=malloc(sizeof(panelnames));
makepanel(&Thanks,"Thanks");
nodelay(panel_window(Thanks->p), FALSE);
top_panel(Thanks->p);
wbkgd(panel_window(Thanks->p),COLOR_PAIR(2));
box(panel_window(Thanks->p),0,0);
update_panels();
doupdate();
refresh();
wrefresh(panel_window(Thanks->p));
mvwprintw(panel_window(Thanks->p),12,3,"Your game has completed and the found words");
mvwprintw(panel_window(Thanks->p),13,3,"have been stored in wordsfound.txt");
mvwprintw(panel_window(Thanks->p),14,3,"Press any key to return to the main menu");
update_panels();
doupdate();
refresh();
wrefresh(panel_window(Thanks->p));
getch();
clear();
//freeing memory from trie
//ran into a bug of I didn't doing multiple games without closing program resulted in a segfault
free(root);
del_panel(Thanks->p);
}
		




//function created to handle panel creation
//makes window reference easier
//pass windowfrom, name, 
void makepanel(panelnames** pn,char* name)
{
	WINDOW* window = newwin(DEFAULTWINY, DEFAULTWINX,OFFSETWINY, OFFSETWINX);
	panelnames* temp=*pn;
	nodelay(window, TRUE);
	temp->name=name;
	temp->p=new_panel(window);
	*pn=temp;
}


//Function to handle the user resizing the window while the game is in progress
//generic and used in menu specific function below
void resizefixer(panelnames* pn)
{
	int currenty=0;
	int currentx=0;
	clear();
	getmaxyx(stdscr,currenty,currentx);
		while (currenty<(DEFAULTWINY+OFFSETWINY+5) || currentx<(DEFAULTWINX+OFFSETWINX+5) )//+5 for visual buffer
		{
		mvprintw(0,0,"Please resize window to be larger until game appears and then close and restart the program");
		getmaxyx(stdscr,currenty,currentx);
		refresh();
		}
	wbkgd(panel_window(pn->p),COLOR_PAIR(2));
	bkgd(COLOR_PAIR(2));
	update_panels();
	doupdate();
	refresh();	
}



//specific resize function for main menu
//handles creation of mainm enu and posting of all main menu elements
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
}





//function called to make retrieval tree
//creates trie based on provided dictionary file
//marks letters as end of word or not for use in 
//finding words that are subsets of other words
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
		}
	}
return temp;
}

//function for finding if  word is present within the trie
//function called in loop to find words 
//character by character in retrieval tree
//returns -1,0, or 1 depending on search resutls
//output is used by word pathing function
int wordsearch(int* path, dictrie* root, board* B, int length)
{
	dictrie* trav=root;
	for (int i = 0; i<length; ++i)
	{
		char x= B->letters[path[i]];
		if (trav->children[x-'A']==NULL)
		{
			return -1;
		}
		trav=trav->children[(int)(x-'A')];
	}
	if (trav->isend)
	{
		return 1;
	}
	return 0;
}

//function to make the adj linked lists for the board
//relies on output from makedice and user input to build board
board* makeboard(char boardletters[], int Bsize) 
{
	int SLength=Bsize*Bsize;
	board* B= malloc(sizeof(board));
	B->verts=SLength;
	B->array=malloc(SLength*sizeof(adjlist*));
	B->letters=malloc((SLength)*sizeof(char));
	for (int i = 0; i < SLength; ++i)
	 {
	 	B->array[i]=malloc(sizeof(adjlist));
	 	B->array[i]->start=calloc(1,sizeof(boardslot));
	 	B->letters[i]=boardletters[i];
	 } 
	 char** matrix=malloc(Bsize*sizeof(char*));
	 for (int i = 0; i < Bsize; ++i)
	 {
	 	matrix[i]=malloc(Bsize*sizeof(char*));
	 }
	 int i=0;
	for (int row = 0; row < Bsize; ++row)
	{
		for (int col = 0; col < Bsize; ++col)
		{
			matrix[row][col]=boardletters[i++];
		}
	}
	int r=0;
	int c=0;
	for (int x = 0; x < SLength; ++x)
	{
	r=floor(x/Bsize);
	c=((x)%Bsize);//interating rows and cols.
		for (int row = -1; row <= 1; row++)
		{
		for (int col = -1; col <= 1; col++)
		{
			if(((c+col)>=0 && (c+col)<Bsize && (r+row)>=0
			 && (r+row)<Bsize) && (((r+row)!=r) || ((c+col)!=c)))
			{
				//calling of function that creates individual nodes on board
				createBnode(B->array[x],matrix[r+row][c+col], x+(Bsize*row)+col);
			}
		}
		}
	
	}
return B;
}



//function to creat the individual board nodes for the makeboard function
void createBnode(adjlist* list, char letter, int I)
{
	adjlist* al=list;
	boardslot* temp_start = al->start;
	boardslot* trav = al->start;
	boardslot* bnode=malloc(sizeof(boardslot));
	//case of node not made yet
	if ((temp_start->letter=='\0'))
	{
	bnode->letter=letter;
	bnode->prev=NULL;
	bnode->next=NULL;
	bnode->index=I;
	*temp_start=*bnode;
	al->start=temp_start;
	return;
	}

	while(trav->next != NULL)
	{
		trav=trav->next;
	}
bnode->index=I;
bnode->letter=letter;
bnode->prev=NULL;
bnode->next=NULL;
trav->next=bnode;
al->start=temp_start;
}

//function to transform pathing array into passable string for wordsearch function
char* path_to_string(board* B,int  path[])
{
	char* string;
	char *buffer = malloc(B->verts*sizeof(char));
	int i =0;
	for (i = 0; i<B->verts; i++)
	{
	buffer[i] ='\0';
	}
	for (i = 0; path[i]!=-1 && i < B->verts; i++)
	{
	buffer[i] = B->letters[i];
	}
string = malloc((i+1)*sizeof(char));
	
	for(int j = 0; j<i;j++)
	{
	string[j] = buffer[j];	
	}
string[i+1]='\0';
return string;	
}

//Overarching function to print out words from moving around the boggle board
//could be improved to not find duplicate words from different paths
//but was not feasible within time constraints
void print_paths(board* gr,int src, int dest, dictrie* root)
{
//get size of graph
int V = gr->verts;
// dynamically allocate arrays that keep track of the path --
int path[V];
// -- and visited nodes
int visited[V];
// initialization to 0;
	for(int i=0; i<V;i++)
	{
	visited[i]=0,path[i]=-1;
	}
//keeps track of index for path array
int path_i=0;
//calling of utility function that actually does most of the pathing work
print_all_pathsU(gr,src, dest,visited,path,path_i,root);
}

//The function that actually traverses the graph and finds all possible paths
//from src to dest.  Takes in current node num (int u), destination (int d)
//the array that keeps track of visited nodes (int visited[]), the array	
//that keeps track of the current path (int path[]), and the  
//index of the path array (int path_index) which is equivalent to path length

void print_all_pathsU(board* B,int u, int d, int visited[],int path[], int path_index, dictrie *root) 
{
	
	char* AP=malloc(path_index*sizeof(char));
	for (int i = 0; i < path_index; ++i)
	{
	AP[i]= '\0';
	}

//add node to path
path[path_index]= u;
//increement path_index/length
path_index+=1;
//mark node as visited
visited[u] = 1;
// printf("%d\n",u);
 int ws_cond= wordsearch(path,root,B,path_index);
	 if (ws_cond==-1)
	 {
	 return;
	 }
	//If current node == destination node
	if(u==d || (path_index>2))
	{	
		//Print out the path to file and add it's score
		if(ws_cond==1)
		{
		int score = (path_index >4) ? 2 : 1;
		score = (path_index > 5) ? 3 : score;
		score = (path_index > 6) ? 5 : score;
		score = (path_index > 7) ? 11 : score;

		
			for(int i=0; i<path_index; i++)
			{
			fprintf(f,"%c",B->letters[path[i]]);
			}
		fprintf(f, " = %dpts \n",score);

		}
	}
		//otherwise...
	if(u!=d)
	{
	//tmp node to traverse the adjacency list at current node (u)
	boardslot* temp = B->array[u]->start;
	//while the node exists
		while(temp !=NULL)
		{
		int i=temp->index;
		//If node hasn't been visited, call recursively using (int i) for the (int u)
		//parameter.
			if(!visited[i])
			{
			//recursive call
			print_all_pathsU(B,i,d,visited,path,path_index, root);
			}
		//next node
		temp=temp->next;
		}
	}
		
	//occurs once all adjacent nodes have been searched
	// or current node == dest node
	
	// reset the path	
	path[path_index] = -1;
	//decrement path_index/length
	// at end of a path, it will decrement back to 0
	path_index--;
	//mark node as not visited
	visited[u]=0;
}

//function to do psuedo rng for letter choice on dice
//not real rng but is random enough that dice should not
//same for multiple games in a row
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


//function to choose the letters from each die and 
//to reuse the dice again for board sizes above the default 4x4
void makedice(int input, char usedletters[])
{
int side /*, i*/, numdice;
srand(time(NULL));  // Seed  based on time
numdice=input*input;
char baseletters[16]={0};

	for (int i = 0; i < numdice; ++i)
	{
	   usedletters[i]=0;
	}
    for (int i = 0; i < numdice; ++i)
    {
    	if (i%16==0)
    	{
       		for(int j=0; j<16; ++j) // generate letters to be used from each die
 			{
	
	        side = randx(6);
			baseletters[j]=die[j][side];
			}
   		}
    usedletters[i]=baseletters[i%16];
    }
}