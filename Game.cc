#include "Game.hh"

#include <unistd.h>

/** Returns true iff the given row in board contains only empty tiles. */
bool rowEmpty(Board* board, unsigned char row);

/** Returns true iff the given row in board contains only non-empty tiles. */
bool rowFull(Board* board, unsigned char row);

/** Sets all tiles in the given row in board to empty. */
void clearRow(Board* board, unsigned char row);

/**
 * Moves a row from board down (to a higher index row), leaving the original
 * row empty.
 * - board: the board to shift a row on
 * - row:   the row to be shifted
 * - shift: a positive number of rows down to move the row
 */
void shiftRow(Board* board, unsigned char row, unsigned char shift);

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
    // Iterate through the tiles of the current piece and add them to the
    // board.
    for (unsigned char i = 0; i < board->activePiece.len; i++) {
        unsigned char tileX = board->activePiece.xPosition
                            + board->activePiece.vertexList[i + 1];
        unsigned char tileY = board->activePiece.yPosition
                            + board->activePiece.vertexList[i];
        board->board[tileY][tileX] = board->activePiece.pieceColor;
    }

    // TODO: verify correct behavior with test case!
    // Start search for full rows from the bottom, clearing them out as they're
    // found. Non-full rows can be shifted down
    unsigned char lastEmpty = 0;
    unsigned char rowsDeleted = 0;
    for (unsigned char i = board->boardHeight - 1; i >= 0; i--) {
        if (rowFull(board, i)) {
            clearRow(board, i);
            rowsDeleted++;
        } else if (!rowEmpty(board, i)) {
            // Non-empty rows need to be shifted downwards by the number of
            // deleted rows. Avoid attempting to shift by 0.
            if (rowsDeleted > 0) {
                shiftRow(board, i, rowsDeleted);
            }
        } else {
            // An empty row was encountered, so no rows remain to be shifted.
            break;
        }
    }
}

bool rowEmpty(Board* board, unsigned char row) {
    for (unsigned char i = 0; i < board->boardWidth; i++) {
        if (board->board[row][i] != EMPTY) {
            return false;
        }
    }
    return true;
}

bool rowFull(Board* board, unsigned char row) {
    for (unsigned char i = 0; i < board->boardWidth; i++) {
        if (board->board[row][i] == EMPTY) {
            return false;
        }
    }
    return true;
}

void clearRow(Board* board, unsigned char row) {
    for (unsigned char i = 0; i < board->boardWidth; i++) {
        board->board[row][i] = EMPTY;
    }
}

void shiftRow(Board* board, unsigned char row, unsigned char shift) {
    for (unsigned char i = 0; i < board->boardWidth; i++) {
        board->board[row + shift][i] = board->board[row][i];
        board->board[row][i] = EMPTY; // Note: is this necessary?
    }
}