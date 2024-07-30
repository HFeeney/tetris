#include "Piece.hh"

#include <cstdlib>

#include "Color.hh"

/**
 * Returns a random, non-empty color
 */
Color randomColor();

/**
 * Generates a piece from the specified template
 * automatically sets xposition and yposition so that the piece has no
 * negative absolute vertices
 */
Piece newPiece(Color color);

Piece newPiece() {
	return newPiece(randomColor());
}

Color randomColor() {
	return static_cast<Color>((rand() % 7) + 1);
}

Piece newPiece(Color color) {
	Piece ret;
	ret.pieceColor = color;
	ret.len = 8;
	ret.vertexList = new char[8];
	char* vl = ret.vertexList;

	vl[0] = 0;
	vl[1] = 0;

	switch (color) {
		case BLUE:
			vl[2] = -1;
			vl[3] = 0;
			vl[4] = -2;
			vl[5] = 0;
			vl[6] = 1;
			vl[7] = 0;
			ret.xPosition = 1;
			ret.yPosition = 2;
			break;
		case YELLOW:
			vl[2] = -1;
			vl[3] = 0;
			vl[4] = 0;
			vl[5] = 1;
			vl[6] = -1;
			vl[7] = 1;
			ret.xPosition = 1;
			ret.yPosition = 2;
			break;
		case RED:
			vl[2] = -1;
			vl[3] = 0;
			vl[4] = -1;
			vl[5] = 1;
			vl[6] = 0;
			vl[7] = -1;
			ret.xPosition = 1;
			ret.yPosition = 2;
			break;
		case GREEN:
			vl[2] = -1;
			vl[3] = 0;
			vl[4] = -1;
			vl[5] = -1;
			vl[6] = 0;
			vl[7] = 1;
			ret.xPosition = 1;
			ret.yPosition = 2;
			break;
		case PURPLE:
			vl[2] = 0;
			vl[3] = -1;
			vl[4] = 0;
			vl[5] = 1;
			vl[6] = -1;
			vl[7] = 0;
			ret.xPosition = 1;
			ret.yPosition = 2;
			break;
		case ORANGE:
			vl[2] = 0;
			vl[3] = -1;
			vl[4] = -1;
			vl[5] = 1;
			vl[6] = 0;
			vl[7] = 1;
			ret.xPosition = 1;
			ret.yPosition = 2;
			break;
		case LILAC:
			vl[2] = 0;
			vl[3] = -1;
			vl[4] = -1;
			vl[5] = -1;
			vl[6] = 0;
			vl[7] = 1;
			ret.xPosition = 1;
			ret.yPosition = 2;
			break;
	}
	return ret;
}