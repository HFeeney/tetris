#include "Display.hh"

#include <stdexcept>

#define SIDE_PANEL_WIDTH 10
#define SCORE_PANEL_HEIGHT 3
#define NEXT_PANEL_HEIGHT 6

/**
 * NOTE:
 * Each tile in the game is represented as side by side characters on the screen
 * This is because characters are too tall on the console to use 1:1 mapping
 */

Display::Display(const Board* const board) : board(board) {
	// board width + lines around board + padding between board and score panel + width of score panel
	int requiredWidth = 2 * board->boardWidth + 3 + SIDE_PANEL_WIDTH;
	int requiredHeight = std::max(board->boardHeight + 2, 1 + SCORE_PANEL_HEIGHT + NEXT_PANEL_HEIGHT);
	gameWindow = subwin(stdscr, requiredHeight, requiredWidth, 0, 0);
	if (!gameWindow) throw std::runtime_error("invalid window size");

	// setup internal windows
	boardWindow = derwin(gameWindow, board->boardHeight + 2, 2 * board->boardWidth + 2, 0, 0);
	nextWindow = derwin(gameWindow, NEXT_PANEL_HEIGHT, SIDE_PANEL_WIDTH, 0, 2 * board->boardWidth + 3);
	scoreWindow = derwin(gameWindow, SCORE_PANEL_HEIGHT, SIDE_PANEL_WIDTH, NEXT_PANEL_HEIGHT + 1, 2 * board->boardWidth + 3);

	// draw boxes around windows
	wborder(boardWindow, 0, 0, 0, 0, 0, 0, 0, 0);
	wrefresh(boardWindow);
	wborder(nextWindow, 0, 0, 0, 0, 0, 0, 0, 0);
	waddstr(nextWindow, "NEXT:");
	wrefresh(nextWindow);
	wborder(scoreWindow, 0, 0, 0, 0, 0, 0, 0, 0);
	waddstr(scoreWindow, "SCORE:");
	wrefresh(scoreWindow);
}

Display::~Display() {
	delwin(scoreWindow);
	delwin(nextWindow);
	delwin(boardWindow);
	delwin(gameWindow);
}

/**
 * Prints the piece in the given window
 * piece is printed in the window at its given position
 */
void wprintPiece(WINDOW* win, const Piece& piece) {
	// print new char
	wattrset(win, COLOR_PAIR(piece.pieceColor));
	for (unsigned char i = 0; i < piece.len; /*incrementation done on next line*/) {
		wmove(win, piece.yPosition + piece.vertexList[i++] + 1, 2 * (piece.xPosition + piece.vertexList[i++]) + 1);
		waddch(win, ' ');
		waddch(win, ' ');
	}
}

void Display::display() {
	// clear board and next
	wclear(boardWindow);
	wclear(nextWindow);
	// redraw borders for windows
	// draw boxes around windows
	wattrset(boardWindow, COLOR_PAIR(EMPTY));
	wborder(boardWindow, 0, 0, 0, 0, 0, 0, 0, 0);
	wattrset(nextWindow, COLOR_PAIR(EMPTY));
	wborder(nextWindow, 0, 0, 0, 0, 0, 0, 0, 0);
	waddstr(nextWindow, "NEXT:");
	
	// print board
	for (int line = 0; line < board->boardHeight; line++) {
		wmove(boardWindow, line + 1, 1);
		for (int col = 0; col < board->boardWidth; col++) {
			wattrset(boardWindow, COLOR_PAIR(board->board[line][col]));
			waddch(boardWindow, ' ');
			waddch(boardWindow, ' ');
		}
	}
	wprintPiece(boardWindow, board->activePiece);
	wrefresh(boardWindow);

	// print next
	wprintPiece(nextWindow, board->nextPiece);
	wrefresh(nextWindow);

	// print score
	char scorestr[SIDE_PANEL_WIDTH - 1];
	snprintf(scorestr, SIDE_PANEL_WIDTH, "%*i", SIDE_PANEL_WIDTH - 2, board->score);
	scorestr[SIDE_PANEL_WIDTH] = '\0';
	for (char* s = scorestr; *s; s++) if (*s == ' ') *s = '0';
	wmove(scoreWindow, 1, 1);
	waddstr(scoreWindow, scorestr);
	wrefresh(scoreWindow);
}