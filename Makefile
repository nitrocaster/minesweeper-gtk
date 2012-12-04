# ---------------------------
# Makefile
#
# mlfong
# ---------------------------

SRCDIR  := source

SOURCES := $(shell find $(SRCDIR) -name "*.cc")
OBJECTS := $(patsubst %.c, %.o, $(SOURCES))

CC      := g++
CFLAGS  := -std=c++11 -pedantic -Wall -Werror -Weffc++ -Wextra -Wshadow -g

all: guiexec

guiexec: $(OBJECTS)
	$(CC) -std=c++11 $^ `pkg-config --cflags --libs gtkmm-2.4` -o Minesweeper

execme: $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o main

clean:
	rm -rf *.out *.o *~ source/*~ Minesweeper main main.dSYM
