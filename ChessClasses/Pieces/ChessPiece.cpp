#include "ChessPiece.h"
#include "../utilities.h"

std::string pieceDescription(const ChessPiece& piece)
{
	const Color color = piece.getColor();
	const Type type = piece.getType();
	const Square square = piece.getSquare();
	return "Color : " + colorToString(color) + " Type : " + typeToString(type) + " Square : " + squareToAlgebraic(square);
}