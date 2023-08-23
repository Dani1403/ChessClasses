#include "ChessPiece.h"

std::string ChessPiece::pieceDescription() const 
{
	return "Color : " + colorToString(getColor()) + "\n" +
		" Type : " + typeToString(getType()) + "\n" +
		" Square : " + squareToAlgebraic(getSquare()) + "\n";
}

std::ostream& operator<<(std::ostream& os, const ChessPiece& piece)
{
	os << "Piece: " << std::endl;
	os << piece.pieceDescription() << std::endl;
	return os;
}