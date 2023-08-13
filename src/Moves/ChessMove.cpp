#include "ChessMove.h"
#include "../ChessGame.h"

bool ChessMove::execute(ChessGame& game) const 
{
	ChessBoard* board = game.getChessBoard();
	board->movePiece(getPieceToMove(), getDest());
	return true;
}

void ChessMove::undo(ChessGame& game) const 
{
	ChessBoard* board = game.getChessBoard();
	board->movePiece(getPieceToMove(), getSource());
}