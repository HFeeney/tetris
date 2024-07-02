#pragma once

#include "Board.hh"

/**
 * Action as indicated by the controller
 */
enum Action {
	NONE = 0, LEFT, RIGHT, DOWN, ROTATE_LEFT, ROTATE_RIGHT
};

/**
 * Controls a single game
 * The Model in MVC
 */
class Controller {
  public:
	inline Controller(const Board* const board) : board(board) { }
	Controller(const Controller&) = delete;
	Controller& operator=(const Controller&) = delete;

	/**
	 * Requests an action from the controller
	 * May block up to the allocated number of milliseconds
	 */
	virtual Action getAction(unsigned int maxTime) = 0;

  protected:
	const Board* const board;
};