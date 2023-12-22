#include "ChessPiece.h"

/*
* Get a string representation of the piece with color, type and position
* @return a string representation of the piece
*/
std::string ChessPiece::pieceDescription() const
{
	return "Color : " + colorToString(getColor()) + "\n" +
		" Type : " + typeToString(getType()) + "\n" +
		" Square : " + squareToAlgebraic(getSquare()) + "\n";
}

/*
* output stream operator for a piece
* @param os the output stream
* @param piece the piece to output
* @return the output stream
*/
std::ostream& operator<<(std::ostream& os, const ChessPiece& piece)
{
	os << "Piece: " << std::endl;
	os << piece.pieceDescription() << std::endl;
	return os;
}