
CC = gcc
CFLAGS = -Wall	
LDFLAGS= -std=c11 -lmenu -lpanel -lncurses -lm -g
OBJFILES = DnDBoggle.o boggle_functions.o
TARGET = Boggle

all: clean $(TARGET) grabdict clean

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

grabdict:
	grep -v "'\|^[A-Z]\|é\|è\|ä\|ç" words> "prelimdict.txt";
	grep -x "^..\+." prelimdict.txt> "dict.txt";
	rm prelimdict.txt



clean:
	rm -f $(OBJFILES)  *~
	
