#include "Promotion.h"
#include "../ChessGame.h"

bool Promotion::execute(ChessGame& game) const
{
	ChessBoard* board = game.getChessBoard();
	board->removePiece(getPieceToMove());
	board->addPiece(getNewPiece());
	return true;
}

void Promotion::undo(ChessGame& game) const
{
	ChessBoard* board = game.getChessBoard();
	board->removePiece(getNewPiece());
	board->addPiece(getPieceToMove());
}