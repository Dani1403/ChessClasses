#include "Rook.h"

bool Rook::isValidMove(const Square& source, const Square& destination) const
{
	return isOnSameCol(source, destination) || isOnSameRow(source, destination);
}
