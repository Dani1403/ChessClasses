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
	board->movePiece(m_pieceToMove, m_destination);
	return true;
}

void Capture::undo(ChessGame& game) const
{

}