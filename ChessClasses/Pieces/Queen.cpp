#include "Queen.h"

bool Queen::isValidMove(const Square& source, const Square& destination) const
{
	return isOnSameRow(source, destination) || isOnSameCol(source, destination) ||
		isOnSameDiag(source, destination);
}
