#include "Knight.h"

bool Knight::isValidMove(const Square& source, const Square& destination) const
{
	return isKnightMove(source, destination);
}
