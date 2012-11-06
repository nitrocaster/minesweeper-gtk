# ---------------------------
# Makefile
#
# mlfong
# ---------------------------

SRCDIR  := source

SOURCES := $(shell find $(SRCDIR) -name "*.cc")
OBJECTS := $(patsubst %.c, %.o, $(SOURCES))

CC      := clang++
CFLAGS  := -std=c++11 -pedantic -Wall -Werror -Weffc++ -Wextra -Wshadow -stdlib=libc++ -g

all: execme

execme: $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o main

clean:
	rm -rf *.out *.o main main.dSYM
