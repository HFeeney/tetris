#pragma once

#include <curses.h>

#include "Board.hh"

/**
 * Class to manage the display of a single game
 * The View in MVC
 */
class Display {
  public:
	Display(const Board* const board);
	Display(const Display&) = delete;
	Display& operator=(const Display&) = delete;
	~Display();

	/**
	 * Draws the board to the screen
	 */
	void display();

  protected:
	const Board* const board;
	// window for entire game (sized perfectly)
	WINDOW* gameWindow;
	// window for just the board
	WINDOW* boardWindow;
	// window for the score panel
	WINDOW* scoreWindow;
	// window for the next piece
	WINDOW* nextWindow;
};