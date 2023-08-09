#include "King.h"

bool King::isValidMove(const Square& source, const Square& destination) const
{
	return dist(source, destination) == 1;
}
