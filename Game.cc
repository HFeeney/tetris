#include "Game.hh"

void Game::play() {
	// while piece successfully spawns continue to play game
	while (spawn()) {
		// play with current piece
		do {
			// check for user movements
			timer.nextUpdate();
			do {
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
			} while (!timer.elapsed());
		} while (move(DOWN));
		place();
	}
}

bool Game::spawn() {
	// TODO
}

bool Game::move(Action direction) {
	// TODO
}

void Game::place() {
	// TODO
}