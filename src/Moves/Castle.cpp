#include "../ChessGame.h"
#include "Castle.h"

/*
* Checks if a castle move is valid
* Checks for :
* - the source square is not empty
* - the color of the piece to move is the color of the current player
* - the king and the rook have not moved yet
* - there is no piece between the king and the rook
* - the king is not in check
* - the king does not pass through a square that is attacked by an enemy piece
* - the king does not end up in check
* - > raise the appropriate exception in case of invalid move
*
* @param game : the game to check the move on
* @return true if the move is valid, otherwise an exception is raised
* @override the ChessMove::checkValidity() function
*/
bool Castle::checkValidity(ChessGame& game) const
{
	const std::shared_ptr<ChessBoard> board = game.getChessBoard();
	if (!m_pieceToMove)
		throw InvalidMove(SOURCE_SQUARE_EMPTY);
	if (board->checkObstacles(m_source, m_destination) && (dynamic_cast<Knight*>(m_pieceToMove.get()) == nullptr))
		throw InvalidMove(OBSTACLE);
	if (m_rookToMove->hasMoved())
		throw InvalidMove(INVALID_CASTLE_ROOK);
	const std::shared_ptr<King> king = std::dynamic_pointer_cast<King>(m_pieceToMove);
	if (king->hasMoved())
		throw InvalidMove(INVALID_CASTLE_KING);
	if (game.isInCheck(game.getCurrentPlayer().getColor()))
		throw InvalidMove(INVALID_CASTLE_CHECK);
	return true;
}

/*
* Apply the move to the current game
* @param game : the game to apply the move to
* @return true if the move was applied, false otherwise
* @override the ChessMove::execute() function
*/
bool Castle::execute(ChessGame& game) const
{
	m_kingMove.execute(game);
	m_rookMove.execute(game);
	return true;
}

/*
* Undo the move on the current game
* @param game : the game to undo the move on
* @override the ChessMove::undo() function
*/
void Castle::undo(ChessGame& game) const
{
	m_kingMove.undo(game);
	m_rookMove.undo(game);
}

/*
* @return a string describing the move
* @override the ChessMove::moveDescription() function
*/
std::string Castle::moveDescription() const
{
	return "Castle: \n" +
		m_kingMove.moveDescription() + "\n" + m_rookMove.moveDescription();
}