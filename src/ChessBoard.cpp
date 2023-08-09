#include "ChessBoard.h"
#include "Moves/ChessMove.h"

void ChessBoardSingleton::removePiece(std::unique_ptr<ChessPiece> piece)
{
	Square pos = piece->getSquare();
	m_board[pos.row][pos.col] = nullptr;
}

void ChessBoardSingleton::addPiece(std::unique_ptr<ChessPiece> piece)
{
	Square pos = piece->getSquare();
	m_board[pos.row][pos.col] = std::move(piece);
}

void ChessBoardSingleton::movePiece(std::unique_ptr<ChessPiece> piece, const Square& destination)
{
	Square source = piece->getSquare();
	m_board[destination.row][destination.col] = std::move(piece);
	m_board[source.row][source.col] = nullptr;
}

bool ChessBoardSingleton::checkRowForObstacle(const Square& src, const Square& dest) const
{
	int row = src.row;
	for (int col = startCol(src, dest) + 1; col != endCol(src, dest); col++)
	{
		if (m_board[row][col] != nullptr)
			return false;
	}
	return true;
}

bool ChessBoardSingleton::checkColForObstacle(const Square& src, const Square& dest) const
{
	int col = src.col;
	for (int row = startRow(src, dest) + 1; row != endRow(src, dest); row++)
	{
		if (m_board[row][col] != nullptr)
			return false;
	}
	return true;
}

bool ChessBoardSingleton::checkDiagForObstacle(const Square& src, const Square& dest) const
{
	for (int row = startRow(src, dest) + 1, col = startCol(src, dest) + 1;
		row < endRow(src, dest) && col < endCol(src, dest); row++, col += isDownwardDiag(src, dest) ? -1 : 1)
	{
		if (m_board[row][col] != nullptr)
			return false;
	}
	return true;
}

bool ChessBoardSingleton::checkObstacles(ChessMove* move) const
{
	Square src = move->getSource();
	Square dest = move->getDest();
	if (isOnSameRow(src, dest))
		return checkRowForObstacle(src, dest);
	else if (isOnSameCol(src, dest))
		return checkColForObstacle(src, dest);
	else if (isOnSameDiag(src, dest))
		return checkDiagForObstacle(src, dest);
	return false;
}

