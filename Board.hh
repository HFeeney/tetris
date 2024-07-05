#pragma once

#include "Color.hh"
#include "Piece.hh"

/**
 * struct representing the state of the board
 * NOTE: only the currently falling piece is represented as a piece,
 *       all other pieces are represented only as tiles on the board
 */
struct Board {
	Board(const unsigned char width, const unsigned char height);
	Board(const Board&) = delete;
	Board& operator=(const Board&) = delete;
	~Board();

	// board size values
	const unsigned char boardWidth, boardHeight;

	// colors of pieces at points on the board
	// EMPTY indicates that the tile does not have a piece in it
	// the board should only show placed pieces; the active piece should not be
	// included on the board
	Color* const* const board;
	
	// current piece and queued piece, respectively
	// the current piece should also be represented as tiles on the board
	Piece activePiece, nextPiece;

	// player score
	unsigned int score;
};