CC=gcc
CXX=g++
CFLAGS=
DFLAGS=-g -Og
BFLAGS=-O2
LFLAGS=
LIBS=-lncurses

debug: override CFLAGS+=$(DFLAGS)
debug: all

build: override CFLAGS+=$(BFLAGS)
build: all

all: tetris

tetris: tetris.o Board.o Display.o Game.o PlayerController.o UpdateTimer.o
	$(CXX) $(LFLAGS) -o $@ $^ $(LIBS)

Board.o: Board.cc Board.hh Color.hh Piece.hh
	$(CXX) $(CFLAGS) -c -o $@ $<

Display.o: Display.cc Display.hh Board.hh Color.hh Piece.hh
	$(CXX) $(CFLAGS) -c -o $@ $<

Game.o: Game.cc Game.hh UpdateTimer.hh Display.hh Board.hh Color.hh Piece.hh Controller.hh
	$(CXX) $(CFLAGS) -c -o $@ $<

PlayerController.o: PlayerController.cc PlayerController.hh Controller.hh Board.hh Color.hh Piece.hh
	$(CXX) $(CFLAGS) -c -o $@ $<

tetris.o: tetris.cc Board.hh Color.hh Piece.hh Display.hh PlayerController.hh Controller.hh Game.hh UpdateTimer.hh
	$(CXX) $(CFLAGS) -c -o $@ $<

UpdateTimer.o: UpdateTimer.cc UpdateTimer.hh
	$(CXX) $(CFLAGS) -c -o $@ $<

clean:
	/bin/rm -f *.o tetris
