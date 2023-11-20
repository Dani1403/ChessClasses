#include "ChessMove.h"
#include "../ChessGame.h"

bool ChessMove::checkValidity(ChessGame& game) const 
{
	std::shared_ptr<ChessBoard> board = game.getChessBoard();
	if (m_pieceToMove->getColor() != game.getCurrentPlayer().getColor())
		throw InvalidMove(NOT_YOUR_COLOR);
	if (board->getPieceAt(m_destination) != nullptr)
		throw InvalidMove(DESTINATION_SQUARE_NOT_EMPTY);
	if (!m_pieceToMove->isValidMove(m_source, m_destination))
		throw InvalidMove(INVALID_MOVEMENT);
	if (board->checkObstacles(m_source, m_destination) && (dynamic_cast<Knight*>(m_pieceToMove.get()) == nullptr))
		throw InvalidMove(OBSTACLE);
	return true;
}

bool ChessMove::execute(ChessGame& game) const 
{
	std::shared_ptr<ChessBoard> board = game.getChessBoard();
	board->movePiece(getPieceToMove(), getDest());
	return true;
}

void ChessMove::undo(ChessGame& game) const 
{
	std::shared_ptr<ChessBoard> board = game.getChessBoard();
	board->movePiece(getPieceToMove(), getSource());
}

std::string ChessMove::moveDescription() const
{
	return "Source: " + squareToAlgebraic(getSource()) + "\n" + 
		"Destination: " + squareToAlgebraic(getDest()) + "\n" + 
		"Piece To Move: \n" + getPieceToMove()->pieceDescription();
}

std::ostream& operator<<(std::ostream& os, const ChessMove& move)
{
	os << "Move: \n" + move.moveDescription();
	return os;
}