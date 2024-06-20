CC=gcc
CXX=g++
CFLAGS=
DFLAGS=-g -Og
BFLAGS=-O2
LFLAGS=
LIBS=

debug: override CFLAGS+=$(DFLAGS)
debug: all

build: override CFLAGS+=$(BFLAGS)
build: all

all:

tetris.o: tetris.cc
	$(CXX) $(CFLAGS) -c -o $@ $<

clean:
	/bin/rm -f *.o
