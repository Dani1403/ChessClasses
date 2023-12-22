#include "ChessBoard.h"
#include "Moves/Capture.h"
#include "Moves/ChessMove.h"
#include "Moves/Castle.h"
#include "Moves/Promotion.h"

//#define DEBUG_CASTLE
//#define DEBUG_GET_MOVE

/*
* Constructor
*/
ChessBoard::ChessBoard()
{
	for (int row = 0; row < BOARD_SIZE; row++)
	{
		for (int col = 0; col < BOARD_SIZE; col++)
			m_board[row][col] = nullptr;
	}
	m_kingPositions[Color::WHITE] = { 0, 4 };
	m_kingPositions[Color::BLACK] = { 7, 4 };
}

/*
* Add the initial pieces to the board
*  @param color - the color of the pieces to add
*/
void ChessBoard::addInitialPieces(const Color color)
{
	int row = (color == Color::WHITE) ? 1 : 6;
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		addPiece(std::make_shared<Pawn>(Pawn(color, { row, i })));
	}
#ifndef DEBUG_GET_MOVE
	row = (color == Color::WHITE) ? 0 : 7;
	addPiece(std::make_shared<Rook>(Rook(color, { row, 0 })));
	addPiece(std::make_shared<King>(King(color, { row, 4 })));
	addPiece(std::make_shared<Rook>(Rook(color, { row, 7 })));
#ifndef DEBUG_CASTLE
	addPiece(std::make_shared<Knight>(Knight(color, { row, 1 })));
	addPiece(std::make_shared<Bishop>(Bishop(color, { row, 2 })));
	addPiece(std::make_shared<Queen>(Queen(color, { row, 3 })));
	addPiece(std::make_shared<Bishop>(Bishop(color, { row, 5 })));
	addPiece(std::make_shared<Knight>(Knight(color, { row, 6 })));
#endif // !DEBUG_CASTLE
#endif // !DEBUG_GET_MOVE
}

/*
* Draw the board with the pieces on it
*/
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
	std::cout << " \t   a\t     b\t       c        d\t   e\t     f\t       g\t h\n" << std::endl;
}

/*
* Remove a certain piece from the board
* @param piece - the piece to remove
*/
void ChessBoard::removePiece(std::shared_ptr<ChessPiece> piece)
{
	const Square pos = piece->getSquare();
	if (m_board[pos.row][pos.col] == nullptr)
		throw PieceNotOnBoard();
	m_board[pos.row][pos.col] = nullptr;
}

/*
* Add a piece to the board
* @param piece - the piece to add
*/
void ChessBoard::addPiece(std::shared_ptr<ChessPiece> piece)
{
	if (!piece)
		return;
	const Square pos = piece->getSquare();
	m_board[pos.row][pos.col] = piece;
  std::shared_ptr<King> king = std::dynamic_pointer_cast<King>(piece);
	if (king)
		addKingPosition(king);
}

/*
* Move a piece to a certain square
* @param piece - the piece to move
* @param destination - the square to move the piece to
*/
void ChessBoard::movePiece(std::shared_ptr<ChessPiece> piece, const Square& destination)
{
	removePiece(piece);
	piece->setPosition(destination);
	addPiece(piece);
}

/*
* Add the king's position to the map
*/
void ChessBoard::addKingPosition(std::shared_ptr<King> king)
{
	m_kingPositions[king->getColor()] = king->getSquare();
}

/*
* Get the king position of a certain color
* @param color - the color of the king
* @return the king position
*/
Square ChessBoard::getKingPosition(const Color color)
{
	return m_kingPositions[color];
}

/*
* Check if there are obstacles between two squares on the same row
* @param src - the source square
* @param dest - the destination square
* @return true if there are obstacles between the squares, false otherwise
*/
bool ChessBoard::checkRowForObstacle(const Square& src, const Square& dest) const
{
	int row = src.row;
	for (int col = startCol(src, dest) + 1; col != endCol(src, dest) && col < 8; col++)
	{
		if (m_board[row][col] != nullptr)
			return true;
	}
	return false;
}

/*
* Check if there are obstacles between two squares on the same column
* @param src - the source square
* @param dest - the destination square
* @return true if there are obstacles between the squares, false otherwise
*/
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

/*
* Check if there are obstacles between two squares on the same diagonal
* @param src - the source square
* @param dest - the destination square
* @return true if there are obstacles between the squares, false otherwise
*/
bool ChessBoard::checkDiagForObstacle(const Square& src, const Square& dest) const
{
	int delta_row = dest.row - src.row;
	int delta_col = dest.col - src.col;

	int rowDir = (delta_row > 0) ? 1 : -1;
	int colDir = (delta_col > 0) ? 1 : -1;

	int row = src.row + rowDir;
	int col = src.col + colDir;

	while (row != dest.row || col != dest.col)
	{
		if (m_board[row][col] != nullptr)
		{
			return true;
		}

		if (row + rowDir != dest.row && col + colDir != dest.col) {
			row += rowDir;
			col += colDir;
		}
		else {
			break;
		}
	}
	return false;
}

/*
* Check if there are obstacles between two squares
* @param src - the source square
* @param dest - the destination square
* @return true if there are obstacles between the squares, false otherwise
*/
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

/*
* Get the piece at a certain square
* @param square - the square to get the piece from
* @return the piece at the square
*/
std::shared_ptr<ChessPiece> ChessBoard::getPieceAt(const Square& square)
{
	if (!isSquareValid(square))
		return nullptr;
	return m_board[square.row][square.col];
}