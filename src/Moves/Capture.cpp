#include "Capture.h"
#include "../ChessGame.h"

bool Capture::isValid(ChessGame& game) const
{
	if (m_pieceToMove->getColor() != game.getCurrentPlayer().getColor())
		return false;
	std::shared_ptr<ChessBoard> board = game.getChessBoard();
	std::shared_ptr<ChessPiece> piece = board->getPieceAt(m_destination);
	if (piece == nullptr || (piece->getColor() != game.getCurrentPlayer().getColor()))
		return false;
	if (board->checkObstacles(m_source, m_destination) && (dynamic_cast<Knight*>(m_pieceToMove.get()) == nullptr))
		return false;
	return true;
}

bool Capture::execute(ChessGame& game) const 
{
	std::shared_ptr<ChessBoard> board = game.getChessBoard();
	board->removePiece(getCapturedPiece());
	board->movePiece(getPieceToMove(), getDest());
	return true; 
}

void Capture::undo(ChessGame& game) const
{
	ChessMove::undo(game);
	game.getChessBoard()->addPiece(getCapturedPiece());
}

std::string Capture::moveDescription() const
{
	return ChessMove::moveDescription() + "\n" +
		"Captured piece: " + getCapturedPiece()->pieceDescription();
}