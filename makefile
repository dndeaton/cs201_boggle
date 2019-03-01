
CC = gcc
CFLAGS = -Wall
LDFLAGS= -std=c11 -lmenu -lpanel -lncurses
OBJFILES = dietestcurses.o boggle_functions.o
TARGET = die

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
	rm -f $(OBJFILES) $(TARGET) *~
	
