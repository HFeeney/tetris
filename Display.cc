#include "Display.hh"

#include <stdexcept>

#define SIDE_PANEL_WIDTH 10
#define SCORE_PANEL_HEIGHT 3
#define NEXT_PANEL_HEIGHT 6

/**
 * NOTE:
 * Each tile in the game is represented as side by side characters on the screen
 * This is because characters are too tall on the console to use 1:1 mapping
 */

Display::Display(const Board* const board) : board(board) {
	// board width + lines around board + padding between board and score panel + width of score panel
	int requiredWidth = 2 * board->boardWidth + 3 + SIDE_PANEL_WIDTH;
	int requiredHeight = std::max(board->boardHeight + 2, 1 + SCORE_PANEL_HEIGHT + NEXT_PANEL_HEIGHT);
	gameWindow = subwin(stdscr, requiredHeight, requiredWidth, 0, 0);
	if (!gameWindow) throw std::runtime_error("invalid window size");

	// setup internal windows
	boardWindow = derwin(gameWindow, board->boardHeight + 2, 2 * board->boardWidth + 2, 0, 0);
	nextWindow = derwin(gameWindow, NEXT_PANEL_HEIGHT, SIDE_PANEL_WIDTH, 0, 2 * board->boardWidth + 3);
	scoreWindow = derwin(gameWindow, SCORE_PANEL_HEIGHT, SIDE_PANEL_WIDTH, NEXT_PANEL_HEIGHT + 1, 2 * board->boardWidth + 3);

	// draw boxes around windows
	wborder(boardWindow, '|', '|', '-', '-', '+', '+', '+', '+');
	wrefresh(boardWindow);
	wborder(nextWindow, '|', '|', '-', '-', '+', '+', '+', '+');
	waddstr(nextWindow, "NEXT:");
	wrefresh(nextWindow);
	wborder(scoreWindow, '|', '|', '-', '-', '+', '+', '+', '+');
	waddstr(scoreWindow, "SCORE:");
	wrefresh(scoreWindow);
}

Display::~Display() {
	delwin(scoreWindow);
	delwin(nextWindow);
	delwin(boardWindow);
	delwin(gameWindow);
}

void Display::display() {
	// TODO
}