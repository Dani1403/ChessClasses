#include "ChessMove.h"
#include "../ChessGame.h"
#include "../Pieces/Knight.h"

bool ChessMove::execute(ChessGame& game) const 
{
	if (!getPieceToMove()->isValidMove(getSource(), getDest()))
		return false;
	ChessBoard* board = game.getChessBoard();
	if (!board->checkObstacles(this) && !dynamic_cast<Knight*>(getPieceToMove()))
		return false;
	board->movePiece(getPieceToMove(), getDest());
	return true;
}

void ChessMove::undo(ChessGame& game) const 
{
	ChessBoard* board = game.getChessBoard();
	board->movePiece(getPieceToMove(), getSource());
}