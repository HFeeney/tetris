#pragma once

#include <curses.h>

#include "Board.hh"

/**
 * Class to manage the display of a single game
 * The View in MVC
 */
class Display {
  public:
	Display(WINDOW* screen, const Board* const board);
	Display(const Display&) = delete;
	Display& operator=(const Display&) = delete;

	/**
	 * Draws the board to the screen
	 */
	void display();

  protected:
	const Board* const board;
};