#include "Rook.h"

/* isValidMove function
* @param source: the square the piece is currently on
* @param destination: the square the piece is trying to move to
* @return: true if the move is valid, false otherwise
* @override: the ChessPiece isValidMove function
*/
bool Rook::isValidMove(const Square& source, const Square& destination) const
{
	return isOnSameCol(source, destination) || isOnSameRow(source, destination);
}
