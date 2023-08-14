#include "ChessPiece.h"

std::string ChessPiece::pieceDescription() const 
{
	return "Color : " + colorToString(m_color) + "\n" +
		" Type : " + typeToString(m_type) + "\n" +
		" Square : " + squareToAlgebraic(m_position);
}

std::ostream& ChessPiece::operator<<(std::ostream& os) const 
{
	os << "Piece" << std::endl;
	os << pieceDescription() << std::endl;
	return os;
}