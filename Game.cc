#include "Game.hh"

#include <unistd.h>

void Game::play() {
	// while piece successfully spawns continue to play game
	while (spawn()) {
		// play with current piece
		do {
			display->display();
			// check for user movements
			timer.nextUpdate();
			do {
				usleep(1000 * INPUT_DELAY_MS);
				Action action = controller->getAction(timer.timeRemaining());
				switch(action) {
					case LEFT:
					case DOWN:
					case RIGHT:
					case ROTATE_LEFT:
					case ROTATE_RIGHT:
						move(action);
						break;
					case NONE:
						break;
				}
				display->display();
			} while (!timer.elapsed());
		} while (move(DOWN));
		place();
	}
}

bool Game::spawn() {
	// TODO
	return true;
}

bool Game::move(Action direction) {
	// TODO
	return true;
}

void Game::place() {
	// TODO
}