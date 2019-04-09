# cs201_boggle
Digital recreation of Boggle game
by David Deaton
for CS 201 Spring 2019
The University of Alabama

#Instructions

Users are to download all files not within the "Old_Unused" folder and save them within the same local directory.
This should include "DnDBoggle.c","boggle_functions.c", "boggle_functions.h", and "makefile".
Users are to include their own dictionary file as described below under "#Creating dictionary"
Users should make sure that they have the ncurses library and its associated sub files installed. 
Specifically "menu.h" and "panel.h". Users MUST size their terminal window to be Fullscreen  or a minimum terminal window size of "75x35" inorder for the program to be playable. If you do not, and resize after startup this can lead to an odd segfault due to how ncurses processes the resizing of the window as a key input. This also mean DO NOT resize the window while the program is running as this will cause the program to segfault. I tried for over a week to fix this and was unable to have resizability working as well as take user input of the board size. I do not know why this is, but it was something I just had to accept.


#Creating dictionary
Users are to procure their own dictionary file from thier linux environment. My dictionary file was created
from the "words" file located in the "usr/share/dict" directory on Ubuntu 18.04. Place this file within the same local directory as the other downloaded files and makes sure the file is name "words" with no file type ie ".txt"

Note: While other dictionary files that are lowercase and have all proper nouns capitalized may work with the makefile.
I have not tested it extensively and cannot say which files will and will not work which my program.


#compiling and running the program
To compile my program you simply need to navigate in Terminal to the local directory in which you downloaded the files
required above. The type "make" and the resulting .o file will be called "Boggle.o"
To run the program simply type "./Boggle" and the program should start. Again I have not tested
this program extensively on multiple compilers and have only worked with the built in compiler on Ubuntu 18.04. 
Users may use other compilers, but I cannot guarantee that they will function properly.


#Video demonstration
Linked here is a youtube video demostrating my program
I am unable to voice over it due to lacking an external microphone to record my audio
as my laptop's builtin microphone would not work on my Ubuntu partition
In the video I demostrate the functions of my program and it's visual limitations

https://youtu.be/V5EovuLmHSE


#Design decisions and Limitations
While coding this program I encountered a few key issues that I eventually had to just allow to exist within my program
The most notable of which are listed here:

>Lack of "Qu" cube:
I was orginally going to code a part of my wordsearch function to automatically appaend a "u" 
to every instance of "Q" that it found while walking the various paths of the board looking for words.
However, this proved much more difficult of a task than I had imagined and due to time constraints
my Boggle recreation does not have a "Qu" cube side and instead only counts the "Q" side of the cubes as "Q" instead of "Qu".
This leads to some generated boards having less word paths than others if a "U" is not coincidentally placed adjacent to the "Q"
 Given more time I would have liked ot have figured out how to implement this logic. But, for now I decided it was more
 important to publish and submit a working less true to the source program than one that was unfinished.
 
 >Duplicate word filtering:
 In my program I wanted to code my path finding function to not find the same word again if it had already encountered that
 word on the current board. However, having persistent visited flags on each node proved to be above my skill level and
 too ambitious for the time constraint I was under. As such my program currently makes use of a multiple file filtering
 system command code block to sort the words found by score and then filter out any duplicates to the final 
 "wordsfound.txt" file. This method works fairly well for larger board than can be displayed within my program
 due to being able to show the found words outside of the ncurses display and saving them in an easily searchable list for player(s) to compute their score.
 
 >Lack of built in player scoring:
 In my program there is currently no user interface way to enter your found words to compute your score. This is due to the above
 stated issues with filtering out duplicate words and ncurses user input. I instead opted to created a sorted "wordsfound.txt"
 file for player(s) to reference on their own. This also allows for players to see all the words they did not find and possibly expand their vocabulary as a result.
 
 >Lack of built in timer system:
 Originially for my program I had wanted to an adjustable timer for each game that would be displayed with the board.
 This however proved to again be a bit too ambitious for my expericance and the time frame I was working in.
 I instead instruct players in the "Rules" window to set their own timer for whatever time they prefer, while listing
 that the standard is 3 minutes. Since they board can be whatever size players want, I decided that allowing them to create
 thier own timer was a better decision.
 
>Possible bugs and/or hardware limitations:
Within my program it is possible to generate upto a ((2^31)-1)x((2^31)-1) board, this limitation is due to how the "atoi"
function returns its integer value as a signed number thereby making it impossible to pass in a higher value. This is also the reason for the 10 digit limitation on number size for user innput. (2^31)-1 is 10 digits, therefore I limited the input string to that length for memory and error preventions sake. Another small flaw that came about due to the functionality of "atoi" in C11
is that my user in put filtering works for strings like "e4" or "r", but not "4ee" or "5t3" due to atoi code. In the case of 
input similar to "30e" or "4r7" my program will interpret that input as "30" and "4" respectively. I wanted to fix this issue, but that would require me to completely rewrite my own "atoi" handler from what I read online. The largest flaw of my program that I have encountered is that while it can generate large boards easily, it can have issues solving them. I was unable to confirm if this is due to hardware limitations or how I coded my program due to time constraints and have to test hardware limitations in very roundabout ways. As it is currently my program can only reliably solve 49x49 size boards in the environment I am using to test (my laptop). Outside of my user interface program I was able to have my program solve a 100x100 board or 100,000 characters, though I believe that may have been due to the pathing of the generated board being very forgiving for how my program walks the board. I also ran into a bug where if several 40x40+ games where played in one session of the program being opened the program will segfault, however I was unable to achieve this a second time despite multiple hours of trying. I feel it might have been due to hardware limitations on my laptop, however due to this I recommend that users restart the program after playing a game using a board larger than 10x10.
 
 
 
 
 #Credit for code and/or coding inspiration
 
 
 >GeeksforGeeks for their implementation of a retrieval tree in c++ that I then ported over to C11
 and for the count less other questions thier documentation answered
 
 >Ubuntu 18.04 for having a built in words list file for the English language and making my life infinitely easier
 
 >Dr. Anderson for pointing me in the right direction on how to approach debugging and for showing me how to use system
 commands within C11 and Ubuntu
 
 >Wikipedia for the rules and components of the Boggle board game that I referenced an innumerable amount of times
 while coding this project
 
 
 >Auren Arevalo, my good friend without whom I would have been way out of my depth with some of my functions
 and possibly would not have finished this project on time. Seriously if there's extra credit for peer assistance he has earned it a million times over. 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
