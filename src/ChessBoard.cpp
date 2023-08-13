#include "ChessBoard.h"
#include "Moves/ChessMove.h"

void ChessBoard::removePiece(ChessPiece* piece)
{
	Square pos = piece->getSquare();
	if (m_board[pos.row][pos.col] == nullptr)
		throw PieceNotOnBoard();
	m_board[pos.row][pos.col] = nullptr;
}

void ChessBoard::addPiece(ChessPiece* piece)
{
	Square pos = piece->getSquare();
	if (m_board[pos.row][pos.col] != nullptr)
		throw SquareNotEmpty();
	m_board[pos.row][pos.col] = piece;
}

void ChessBoard::movePiece(ChessPiece* piece, const Square& destination)
{
	removePiece(piece);
	piece->setPosition(destination);
	addPiece(piece);
}

bool ChessBoard::checkRowForObstacle(const Square& src, const Square& dest) const
{
	int row = src.row;
	for (int col = startCol(src, dest) + 1; col != endCol(src, dest); col++)
	{
		if (m_board[row][col] != nullptr)
			return false;
	}
	return true;
}

bool ChessBoard::checkColForObstacle(const Square& src, const Square& dest) const
{
	int col = src.col;
	for (int row = startRow(src, dest) + 1; row != endRow(src, dest); row++)
	{
		if (m_board[row][col] != nullptr)
			return false;
	}
	return true;
}

bool ChessBoard::checkDiagForObstacle(const Square& src, const Square& dest) const
{
	for (int row = startRow(src, dest) + 1, col = startCol(src, dest) + 1;
		row < endRow(src, dest) && col < endCol(src, dest); row++, col += isDownwardDiag(src, dest) ? -1 : 1)
	{
		if (m_board[row][col] != nullptr)
			return false;
	}
	return true;
}

bool ChessBoard::checkObstacles(const ChessMove* move) const
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

ChessPiece* ChessBoard::getPieceAt(const Square& square) const
{
	return m_board[square.row][square.col];
}