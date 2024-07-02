#pragma once

#include <time.h>

#include "UpdateTimer.hh"
#include "Display.hh"
#include "Controller.hh"
#include "Board.hh"

const unsigned int FRAME_TIME_MS = 10;

/**
 * Class to manage a single game instance
 * The controller in MVC
 */
class Game {
  public:
	/**
	 * Creates a new game with the given board, display, and controller
	 */
	inline Game(Board* board, Display* display, Controller* controller) :
		timer(FRAME_TIME_MS),
		board(board),
		score(0),
		display(display),
		controller(controller) { }
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;

	/**
	 * Plays a game
	 * Does not return until game finishes
	 */
	void play();

	/**
	 * Returns the score of the game
	 */
	inline unsigned int getScore() const { return score; }

  private:
	FrameTimer timer;
	Board* board;
	unsigned int score;

	Display* display;
	Controller* controller;
};