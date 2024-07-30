#pragma once

#include <ctime>

#include "UpdateTimer.hh"
#include "Display.hh"
#include "Controller.hh"
#include "Board.hh"

// delay between user actions
#define INPUT_DELAY_MS 500

// time between tile move-downs
const unsigned int FRAME_TIME_MS = 1000;

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
		display(display),
		controller(controller) { }
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;

	/**
	 * Plays a game
	 * Does not return until game finishes
	 */
	void play();

  private:
	/**
	 * Spawns the next brick into the game and generates a new next brick
	 * Returns true iff the spawn was successful
	 */
	bool spawn();

	/**
	 * Effects the desired action upon the active piece
	 * Returns true iff the action was successful
	 * Action must be a movement action (LEFT, DOWN, RIGHT, LEFT_ROTATION, RIGHT_ROTATION)
	 */
	bool move(Action direction);

	/**
	 * Places the current brick where it is
	 * Then checks for and deletes any full rows and shifts any
	 * rows above them down
	 * Updates score
	 * NOTE: this method may cause animations to be played
	 */
	void place();

	UpdateTimer timer;
	Board* board;

	Display* display;
	Controller* controller;
};