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

void ChessBoard::draw()
{
	int rowNum = 0;
	for (auto row = m_board.rbegin(); row != m_board.rend(); ++row, ++rowNum)
	{
		std::cout << BOARD_SIZE - rowNum << "\t";
		for (auto piece = row->begin(); piece != row->end(); ++piece)
		{
			if (*piece == nullptr)
			{
				std::cout << "        | ";
				continue;
			}
			std::cout << colorToString((* piece)->getColor()) + " " + typeToString((*piece)->getType()) + " | ";
		}
		std::cout << "\n" << "       ------------------------------------------------------------------------------" << std::endl;
	}
	std::cout << " \t   a\t     b\t       c        d\t   e\t     f\t       g\t h\n";
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
			return true;
	}
	return false;
}

bool ChessBoard::checkColForObstacle(const Square& src, const Square& dest) const
{
	int col = src.col;
	for (int row = startRow(src, dest) + 1; row != endRow(src, dest); row++)
	{
		if (m_board[row][col] != nullptr)
			return true;
	}
	return false;
}

bool ChessBoard::checkDiagForObstacle(const Square& src, const Square& dest) const
{
	int offset = isDownwardDiag(src, dest) ? -1 : 1;
	for (int row = startRow(src, dest) + 1, col = startCol(src, dest) + offset;
		row < endRow(src, dest) && col < endCol(src, dest); row++, col += offset)
	{
		if (m_board[row][col] != nullptr)
		{
			std::cout << *(m_board[row][col]) << std::endl;
			return true;
		}
	}
	return false;
}

bool ChessBoard::checkObstacles(const Square& src, const Square& dest) const
{
	if (isOnSameRow(src, dest))
		return checkRowForObstacle(src, dest);
	else if (isOnSameCol(src, dest))
		return checkColForObstacle(src, dest);
	else if (isOnSameDiag(src, dest))
		return checkDiagForObstacle(src, dest);
	return false;
}

std::vector<std::shared_ptr<ChessMove>> ChessBoard::getPossibleMoves(std::shared_ptr<ChessPiece> piece)
{
	/*
* Check for :
* Regular / Capture
* Castle if King
* Promotion / En Passant if Pawn
*/
	return std::vector<std::shared_ptr<ChessMove>>();
}

std::shared_ptr<ChessPiece> ChessBoard::getPieceAt(const Square& square)
{
	return m_board[square.row][square.col];
}