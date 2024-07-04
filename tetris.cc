#include <stdlib.h>
#include <curses.h>

#include "Board.hh"
#include "Display.hh"
#include "PlayerController.hh"
#include "Game.hh"

/**
 * Temp function
 * Creates and plays a game
 */
void createGame() {
	//   1. create board
	//   2. create display and controller
	//   3. create game
	//   4. play game

	Board gameboard(10, 20);
	Display screenDisplay(&gameboard);
	PlayerController playerInput;
	Game game(&gameboard, &screenDisplay, &playerInput);
	game.play();
}

int main() {
	initscr();
	cbreak();
	noecho();
	intrflush(stdscr, FALSE);
	keypad(stdscr, TRUE);

	//createGame();
	Board gameboard(10, 20);
	Display screenDisplay(&gameboard);
	while(true);

	endwin();
	return EXIT_SUCCESS;
}
