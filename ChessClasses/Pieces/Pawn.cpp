#include "Pawn.h"

bool Pawn::isValidMove(const Square& source, const Square& destination) const
{
	return isOnSameCol(source, destination) && (destination.row == source.row + 1) ;
}

bool Pawn::isValidCapture(const Square& source, const Square& destination) const
{
	return isOnSameDiag(source, destination) && (destination.row == source.row + 1);
}