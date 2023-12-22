#include "Knight.h"

/*
* isValidMove function using the Knight's movement rules declared in utilities.h
* @param source: the square the piece is currently on
* @param destination: the square the piece is trying to move to
* @return: true if the move is valid, false otherwise
* @override: the ChessPiece isValidMove function
*/
bool Knight::isValidMove(const Square& source, const Square& destination) const
{
	return isKnightMove(source, destination);
}
