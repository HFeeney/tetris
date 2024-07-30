#include "UpdateTimer.hh"

#include <algorithm>

UpdateTimer::UpdateTimer(const unsigned int updateInterval) : 
	updateInterval(updateInterval),
	intervalEndpoint(std::chrono::steady_clock::now() + std::chrono::milliseconds(updateInterval)) { }

unsigned int UpdateTimer::timeRemaining() {
	long long dur = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - intervalEndpoint).count();
	return static_cast<unsigned int>(std::max(dur, 0ll));
}

bool UpdateTimer::elapsed() {
	return intervalEndpoint < std::chrono::steady_clock::now();
}

void UpdateTimer::nextUpdate() {
	intervalEndpoint = std::chrono::steady_clock::now() + std::chrono::milliseconds(updateInterval);
}