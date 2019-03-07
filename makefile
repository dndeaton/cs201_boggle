
CC = gcc
CFLAGS = -Wall
LDFLAGS= -std=c11 -lmenu -lpanel -lncurses
OBJFILES = triemake.o boggle_functions.o
TARGET = trie

all: $(TARGET) grabdict clean

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

grabdict:
	grep -v "'\|^[A-Z]\|é\|è\|ä\|ç" /usr/share/dict/words> "prelimdict.txt";
	grep -x "^..\+." prelimdict.txt> "dict.txt";
	rm prelimdict.txt



clean:
	rm -f $(OBJFILES)  *~
	
