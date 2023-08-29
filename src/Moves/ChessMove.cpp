#include "ChessMove.h"
#include "../ChessGame.h"

bool ChessMove::isValid(ChessGame& game) const 
{
	bool success = true;
	if (m_pieceToMove->getColor() != game.getCurrentPlayer().getColor())
		success = false;
	std::shared_ptr<ChessBoard> board = game.getChessBoard();
	if (board->getPieceAt(m_destination) != nullptr)
		success = false;
	if (board->checkObstacles(m_source, m_destination) && (dynamic_cast<Knight*>(m_pieceToMove.get()) == nullptr))
		success = false;
	execute(game);
	if (game.isInCheck(m_pieceToMove->getColor()))
		success = false;
	undo(game);
	return success;
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