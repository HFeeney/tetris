#pragma once

#include <chrono>

/**
 * A class to easily manage the time left in each game update
 */
class UpdateTimer {
  public:
	/**
	 * Constructs a new update timer with the given update interval in milliseconds
	 */
	UpdateTimer(const unsigned int updateInterval);
	UpdateTimer(const UpdateTimer&) = delete;
	UpdateTimer& operator=(const UpdateTimer&) = delete;

	/**
	 * returns the number of milliseconds left in the current update, or zero if the update has elapsed
	 */
	unsigned int timeRemaining();

	/**
	 * Returns true iff the current update is elapsed
	 */
	bool elapsed();

	/**
	 * Advances the timer to the next update
	 */
	void nextUpdate();

  private:
	const unsigned int updateInterval;
	std::chrono::time_point<std::chrono::steady_clock> intervalEndpoint;
};