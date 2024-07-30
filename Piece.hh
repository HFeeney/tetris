#pragma once

#include "Color.hh"

/**
 * Struct representing a single piece
 * 
 * An example of this struct is the three way connector piece:
 * 
 *       X
 *       XX
 *       X
 * 
 * This piece would have a vertexList of { 0, 0, -1, 0, 0, 1, 1, 0 },
 * and would rotate around the center tile
 */
struct Piece {
	Color pieceColor;

	// global position of the piece
	unsigned char xPosition, yPosition;

	// length of the array vertexList
	// Must be even
	unsigned char len;
	
	// array of local coordinates of the tiles in this piece
	// formatted in the form of:
	//   { y1, x1, y2, x2, ... }
	char* vertexList = nullptr;
};

/**
 * Randomly generates a new piece
 * automatically sets xposition and yposition so that the piece has no
 * negative absolute vertices
 */
Piece newPiece();