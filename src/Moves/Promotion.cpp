#include "Promotion.h"
#include "../ChessGame.h"

std::string Promotion::moveDescription() const
{
	return ChessMove::moveDescription() + "\n Promoted piece: " + 
		getNewPiece()->pieceDescription();
}

bool Promotion::checkValidity(ChessGame& game) const
{
	return ChessMove::checkValidity(game);
}

bool Promotion::execute(ChessGame& game) const
{
	const std::shared_ptr<ChessBoard> board = game.getChessBoard();
	board->removePiece(getPieceToMove());
	board->addPiece(getNewPiece());
	return true;
}

void Promotion::undo(ChessGame& game) const
{
	std::shared_ptr<ChessBoard> board = game.getChessBoard();
	board->removePiece(getNewPiece());
	board->addPiece(getPieceToMove());
}