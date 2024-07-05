#include "Board.hh"

Board::Board(const unsigned char height, const unsigned char width) : boardWidth(width), boardHeight(height), board(new Color*[height]), score(0) {
	Color* arr = new Color[height * width];
	for (int i = 0; i < height; i++) {
		board[i] = arr;
		arr += width;
	}
}

Board::~Board() {
	delete[] board[0];
	delete[] board;
}