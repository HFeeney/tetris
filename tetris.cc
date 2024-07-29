#include <cstdlib>
#include <ctime>
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

	Board gameboard(20, 10);
	Display screenDisplay(&gameboard);
	PlayerController playerInput;
	Game game(&gameboard, &screenDisplay, &playerInput);
	game.play();
}

int main() {
	initscr();
	start_color();
	cbreak();
	noecho();
	curs_set(0);
	intrflush(stdscr, FALSE);
	keypad(stdscr, TRUE);
	srand(time(nullptr));

	// init colors
	init_pair(EMPTY, COLOR_WHITE, COLOR_BLACK);
	init_pair(BLUE, COLOR_WHITE, COLOR_BLUE);
	init_pair(YELLOW, COLOR_WHITE, COLOR_YELLOW);
	init_pair(RED, COLOR_WHITE, COLOR_RED);
	init_pair(GREEN, COLOR_WHITE, COLOR_GREEN);
	init_pair(PURPLE, COLOR_WHITE, COLOR_MAGENTA);
	init_pair(ORANGE, COLOR_WHITE, COLOR_WHITE);
	init_pair(LILAC, COLOR_WHITE, COLOR_CYAN);

	createGame();

	endwin();
	return EXIT_SUCCESS;
}
