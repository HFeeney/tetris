#pragma once

#include "Controller.hh"

/**
 * A controller linked to standard player inputs
*/
class PlayerController : public Controller {
  public:
	inline PlayerController() = default;
	PlayerController(const PlayerController&) = delete;
	PlayerController& operator=(const PlayerController&) = delete;

	/**
	 * Requests an action from the controller
	 * May block up to the allocated number of milliseconds
	 */
	virtual Action getAction(unsigned int maxTime);
};