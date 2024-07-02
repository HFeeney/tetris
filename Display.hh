#pragma once

#include "Board.hh"

/**
 * Class to manage the display of a single game
 * The View in MVC
 */
class Display {
  public:
	inline Display(const Board* const board) : board(board) { }
	Display(const Display&) = delete;
	Display& operator=(const Display&) = delete;

	/**
	 * Draws the board to the screen
	 */
	virtual void display() = 0;

  protected:
	const Board* const board;
};