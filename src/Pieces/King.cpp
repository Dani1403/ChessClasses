#include "King.h"

/* isValidMove function
* @param source: the square the piece is currently on
* @param destination: the square the piece is trying to move to
* @return: true if the move is valid, false otherwise
* @override: the ChessPiece isValidMove function
* the move is valid if the destination square is one square away from the source square
*/
bool King::isValidMove(const Square& source, const Square& destination) const
{
	return dist(source, destination) == 1;
}
