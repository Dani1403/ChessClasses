#include "Capture.h"
#include "../ChessGame.h"

bool Capture::isValid(ChessGame& game) const
{
	std::shared_ptr<ChessBoard> board = game.getChessBoard();
	std::shared_ptr<ChessPiece> piece = board->getPieceAt(m_destination);
	if (!ChessMove::isValid(game) && (piece == nullptr))
		return false;
	if (piece == nullptr || (piece->getColor() != game.getCurrentPlayer().getColor()))
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