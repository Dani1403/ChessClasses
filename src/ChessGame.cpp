#include "ChessGame.h"

ChessGame::ChessGame()
{
	m_chessBoard->initBoard();
}

bool ChessGame::isInCheck(Color color)
{
	Square kingPos = m_chessBoard->getKingPosition(color);
	for (const auto& row : m_chessBoard->getBoard())
	{
		for (std::shared_ptr<ChessPiece> piece : row)
		{
			ChessMove capture = Capture(piece->getSquare(), kingPos, piece, m_chessBoard->getPieceAt(kingPos));
			if (capture.execute(*this)) 
			{
				capture.undo(*this);
				return true;
			}
		}
	}
	return false;
}

void ChessGame::makeMove(std::shared_ptr<ChessMove> move)
{
	std::cout << "Applied" << move;
	m_moves.push_back(move);
	move->execute(*this);
}

void ChessGame::undo()
{
	std::shared_ptr<ChessMove> move = m_moves.back();
	if (move != nullptr)
		move->undo(*this);
	m_moves.pop_back();
}