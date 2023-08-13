#include "Capture.h"
#include "../ChessGame.h"
#include "../Pieces/Knight.h"

bool Capture::execute(ChessGame& game) const 
{
	if (!getPieceToMove()->isValidCapture(getSource(), getDest()))
		return false;
	ChessBoard* board = game.getChessBoard();
	if (!board->checkObstacles(this) && !dynamic_cast<Knight*>(getPieceToMove()))
		return false;
	board->removePiece(getCapturedPiece());
	board->movePiece(getPieceToMove(), getDest());
	return true; 
}

void Capture::undo(ChessGame& game) const
{
	ChessMove::undo(game);
	game.getChessBoard()->addPiece(getCapturedPiece());
}