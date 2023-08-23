#include "ChessBoard.h"
#include "Moves/Capture.h"

ChessBoard::ChessBoard()
{
	for (int row = 0; row < BOARD_SIZE; row++)
	{
		for (int col = 0; col < BOARD_SIZE; col++)
			m_board[row][col] = nullptr;
	}
}

void ChessBoard::addInitialPieces(Color color)
{
	int row = (color == Color::WHITE) ? 1 : 6;
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		addPiece(std::make_shared<Pawn>(Pawn(color, { row, i })));
	}
	row = (color == Color::WHITE) ? 0 : 7;
	addPiece(std::make_shared<Rook>(Rook(color, { row, 0 })));
	addPiece(std::make_shared<Knight>(Knight(color, { row, 1 })));
	addPiece(std::make_shared<Bishop>(Bishop(color, { row, 2 })));
	addPiece(std::make_shared<Queen>(Queen(color, { row, 3 })));
	addPiece(std::make_shared<King>(King(color, { row, 4 })));
	addPiece(std::make_shared<Bishop>(Bishop(color, { row, 5 })));
	addPiece(std::make_shared<Knight>(Knight(color, { row, 6 })));
	addPiece(std::make_shared<Rook>(Rook(color, { row, 7 })));
}

void ChessBoard::initBoard()
{
	addInitialPieces(Color::WHITE);
	addInitialPieces(Color::BLACK);
	for (int row = 2; row < 6; row++)
	{
		for (int col = 0; col < BOARD_SIZE; col++)
			m_board[row][col] = nullptr;
	}
}

void ChessBoard::removePiece(std::shared_ptr<ChessPiece> piece)
{
	Square pos = piece->getSquare();
	if (m_board[pos.row][pos.col] == nullptr)
		throw PieceNotOnBoard();
	m_board[pos.row][pos.col] = nullptr;
}

void ChessBoard::addKingPosition(std::shared_ptr<King> king)
{
	m_kingPositions[king->getColor()] = king->getSquare();
}

Square ChessBoard::getKingPosition(Color color)
{
	return m_kingPositions[color];
}

void ChessBoard::addPiece(std::shared_ptr<ChessPiece> piece)
{
	if (!piece)
		return;
	Square pos = piece->getSquare();
	if (m_board[pos.row][pos.col] != nullptr)
		throw SquareNotEmpty();
	m_board[pos.row][pos.col] = piece;
	std::shared_ptr<King> king = std::dynamic_pointer_cast<King>(piece);
	if (king)
		addKingPosition(king);
}

void ChessBoard::movePiece(std::shared_ptr<ChessPiece> piece, const Square& destination)
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

std::shared_ptr<ChessPiece> ChessBoard::getPieceAt(const Square& square) const
{
	return m_board[square.row][square.col];
}