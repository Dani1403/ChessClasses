#include "ChessGame.h"

void ChessGame::addPawns(ChessBoard* board, Color color)
{
	int row = (color == Color::WHITE) ? 1 : 6;
	for (int i = 0; i < board->BOARD_SIZE; i++)
	{
		board->addPiece(new Pawn(color, { row, i }));
	}
}

void ChessGame::addPieces(ChessBoard* board, Color color)
{
	int row = (color == Color::WHITE) ? 0 : 7;
	board->addPiece(new Rook(color, { row, 0 }));
	board->addPiece(new Knight(color, { row, 1 }));
	board->addPiece(new Bishop(color, { row, 2 }));
	board->addPiece(new Queen(color, { row, 3 }));
	board->addPiece(new King(color, { row, 4 }));
	board->addPiece(new Bishop(color, { row, 5 }));
	board->addPiece(new Knight(color, { row, 6 }));
	board->addPiece(new Rook(color, { row, 7 }));
}

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

void ChessGame::makeMove(ChessMove* move)
{
	std::cout << "Applied" << move;
	m_moves.push_back(move);
	move->execute(*this);
}

void ChessGame::undo()
{
	ChessMove* move = m_moves.back();
	if (move != nullptr)
		move->undo(*this);
	m_moves.pop_back();
}