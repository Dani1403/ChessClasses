#include "Regular.h"
#include "../ChessGame.h"

bool Regular::execute(ChessGame& game) const
{
	ChessBoard* board = game.getChessBoard();
	if (!board->checkObstacles(this))
		return false;
	board->movePiece(m_pieceToMove, m_destination);
	return true;
}

void Regular::undo(ChessGame& game) const
{
	ChessBoard* board = game.getChessBoard();
	board->movePiece(m_pieceToMove, m_source);
}
