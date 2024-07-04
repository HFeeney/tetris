#pragma once

#include "Color.hh"

/**
 * Struct representing a single piece
 * 
 * An example of this struct is the three way connector piece:
 * 
 *       X
 *      XXX
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
	//   { x1, y1, x2, y2, ... }
	char* vertexList;
};