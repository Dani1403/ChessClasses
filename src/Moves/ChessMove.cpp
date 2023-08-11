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
	try 
	{
		board->movePiece(m_pieceToMove, m_destination);
	}
	catch (const std::exception& e) {
		return false;
	}
	return true;
}

void ChessMove::undo(ChessGame& game) const 
{
	ChessBoard* board = game.getChessBoard();
	board->movePiece(m_pieceToMove, m_source);
}