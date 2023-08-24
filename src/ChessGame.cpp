#include "ChessGame.h"

ChessGame::ChessGame() : m_chessBoard(std::make_shared<ChessBoard>(ChessBoard()))
{
	initBoard();
}

void ChessGame::initBoard()
{
	m_chessBoard->addInitialPieces(Color::WHITE);
	m_chessBoard->addInitialPieces(Color::BLACK);
}

void ChessGame::makeMove(std::shared_ptr<ChessMove> move)
{
	/*
	* TODO : check logic with board functions (obstacles, check, ...)
	*/
	m_moves.push_back(move);
	move->execute(*this);
	if (isInCheck(move->getPieceToMove()->getColor()))
		std::cout << "Invalid move";
	std::cout << "Applied: \n" << *move;
}

void ChessGame::undo()
{
	std::shared_ptr<ChessMove> move = m_moves.back();
	if (move != nullptr)
		move->undo(*this);
	m_moves.pop_back();
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

bool ChessGame::isInCheckmate(Color color)
{
	if (!isInCheck(color))
		return false;
	return true;
	/*
	* For each remaining piece of the color
	* Get all the available moves
	* If after the move the color is no more in check return false
	*		otherwise continue
	* return true;
	*/
}

bool ChessGame::isGameOver()
{
	/*
	* Ideally implemented with stalemate and repetitions
	*/
	return (isInCheckmate(Color::BLACK) || isInCheckmate(Color::WHITE));
}