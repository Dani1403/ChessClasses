#include "Pawn.h"

/* isValidMove function
* @param source: the square the piece is currently on
* @param destination: the square the piece is trying to move to
* @return: true if the move is valid, false otherwise
* @override: the ChessPiece isValidMove function
*/
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

/* isValidCapture function
* @param source: the square the piece is currently on
* @param destination: the square the piece is trying to capture
* @return: true if the capture is valid, false otherwise
* @override: the ChessPiece isValidCapture function
*/
bool Pawn::isValidCapture(const Square& source, const Square& destination) const
{
	return isOnSameDiag(source, destination) &&
		(destination.row == source.row + (m_color == Color::WHITE ? 1 : -1));
}