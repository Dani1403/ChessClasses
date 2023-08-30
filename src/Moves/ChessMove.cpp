#include "ChessMove.h"
#include "../ChessGame.h"

bool ChessMove::checkValidity(ChessGame& game) const 
{
	if (m_pieceToMove->getColor() != game.getCurrentPlayer().getColor())
		throw InvalidMove("The piece you want to move is not of your color");
	std::shared_ptr<ChessBoard> board = game.getChessBoard(); 
	if (board->getPieceAt(m_destination) != nullptr)
		throw InvalidMove("There is already a piece at the destination");
	if (!m_pieceToMove->isValidMove(m_source, m_destination))
		throw InvalidMove("Invalid movement for this piece");
	if (board->checkObstacles(m_source, m_destination) && (dynamic_cast<Knight*>(m_pieceToMove.get()) == nullptr))
		throw InvalidMove("There is an obstacle");
	execute(game);
	if (game.isInCheck(m_pieceToMove->getColor()))
		throw InvalidMove("The move results in you being in check");
	undo(game);
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