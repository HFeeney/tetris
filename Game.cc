#include "Game.hh"

#include <unistd.h>

void Game::play() {
    board->nextPiece = newPiece();
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
    // move new piece onto board
    board->activePiece = board->nextPiece;
    // get next piece
    board->nextPiece = newPiece();
    // center new piece
    board->activePiece.xPosition = board->boardWidth / 2;
    // find and set y position as high up as contains piece within board
    char min = 0;
    for (unsigned char i = 0; i < board->activePiece.len; i += 2) {
        if (board->activePiece.vertexList[i] < min) min = board->activePiece.vertexList[i];
    }
    board->activePiece.yPosition = -min;

    // check overlap with other pieces
    for (unsigned char i = 0; i < board->activePiece.len; i += 2) {
        if (board->board[board->activePiece.yPosition + board->activePiece.vertexList[i]][board->activePiece.xPosition + board->activePiece.vertexList[i + 1]] != EMPTY) {
            return false;
        }
    }
	return true;
}

bool Game::move(Action direction) {
    // Simulate making the move, recording new piece attributes after action.
    unsigned char newX = board->activePiece.xPosition, 
                  newY = board->activePiece.yPosition;
    unsigned char activePieceLen = board->activePiece.len;
    char newVertexList[activePieceLen];
    for (unsigned char i = 0; i < activePieceLen; i++) {
        newVertexList[i] = board->activePiece.vertexList[i];
    }

    switch(direction) {
        case LEFT:
            newX--;
            break;
        case DOWN:
            newY++;
            break;
        case RIGHT:
            newX++;
            break;
        case ROTATE_LEFT:
            // Iterate through coordinate pairs and apply rotation to them.
            for (unsigned char i = 0; i < activePieceLen; i += 2) {
                char x = newVertexList[i + 1];
                char y = newVertexList[i];

                // Apply left rotation. x = -y, y = x
                newVertexList[i + 1] = -y;
                newVertexList[i] = x;
            }
            break;
        case ROTATE_RIGHT:
            // Iterate through coordinate pairs and apply rotation to them.
            for (unsigned char i = 0; i < activePieceLen; i += 2) {
                char x = newVertexList[i + 1];
                char y = newVertexList[i];

                // Apply right rotation. x = y, y = -x
                newVertexList[i + 1] = y;
                newVertexList[i] = -x;
            }
            break;
        case NONE:
            break;
    }

    // To know if movement was successful, check whether piece's tiles will
    // - be contained within board
    // - not be overlapping with any other existing tiles
    // after making this move.
    for (unsigned char i = 0; i < activePieceLen; i += 2) {
        char tileX = newX + newVertexList[i + 1];
        char tileY = newY + newVertexList[i];

        // In bounds check.
        if (tileX < 0 || tileX >= board->boardWidth || tileY < 0
                || tileY >= board->boardHeight) {
            return false;
        }

        // Overlap check.
        if (board->board[tileY][tileX] != EMPTY) {
            return false;
        }
    }

    // The move is valid. Make the move by updating the board's active piece.
    // - coordinates
    // - vertex list
    board->activePiece.xPosition = newX;
    board->activePiece.yPosition = newY;
    for (unsigned char i = 0; i < activePieceLen; i++) {
        board->activePiece.vertexList[i] = newVertexList[i];
    }
	return true;
}

void Game::place() {
	// TODO (just fill in board[][] with active piece data)
}