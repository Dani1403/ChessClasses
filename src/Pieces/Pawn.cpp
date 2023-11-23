#include "Pawn.h"

bool Pawn::isValidMove(const Square& source, const Square& destination) const
{
	if (isOnSameCol(source, destination)) {
		if (!m_hasMoved)
			return (destination.row == source.row + (m_color == Color::WHITE ? 1 : -1)) || 
				(destination.row == source.row + (m_color == Color::WHITE ? 2 : -2));
		else
			return (destination.row == source.row + (m_color == Color::WHITE ? 1 : -1));
	}
	return false;
}

bool Pawn::isValidCapture(const Square& source, const Square& destination) const
{
	return isOnSameDiag(source, destination) && 
		(destination.row == source.row + (m_color == Color::WHITE ? 1 : -1));
}

int Pawn::colForPromotion() const
{
	return getSquare().col;
}