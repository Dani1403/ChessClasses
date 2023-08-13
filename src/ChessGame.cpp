#include "ChessGame.h"

bool ChessGame::isInCheck(Color color)
{
	ChessBoard* board = getChessBoard();
	Square kingPos = board->getKingPosition(color);
	for (const auto& row : board->getBoard())
	{
		for (ChessPiece* piece : row)
		{
			ChessMove capture = Capture(piece->getSquare(), kingPos, piece, board->getPieceAt(kingPos));
			if (capture.execute(*this)) 
			{
				capture.undo(*this);
				return true;
			}
		}
	}
	return false;
}
