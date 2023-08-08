#include "Bishop.h"

bool Bishop::isValidMove(const Square& source, const Square& destination) const 
{
	return isOnSameDiag(source, destination);
}