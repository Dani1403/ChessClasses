#include "utilities.h"

bool isSquareValid(const Square& square)
{
	return square.row >= 1 && square.row <= 8 && square.col >= 1 && square.col <= 8;
}

Square algebraicToSquare(const std::string& notation)
{
	int col = notation[0] - 'a';
	int row = notation[1] - '0';
	return Square{ row, col };
}

std::string squareToAlgebraic(const Square& square)
{
	char col = 'a' + square.col;
	char row = '0' + square.row;
	return std::string{ col, row };
}

bool isOnSameRow(const Square& s1, const Square& s2)
{
	return (s1.row == s2.row);
}

bool isOnSameCol(const Square& s1, const Square& s2)
{
	return (s1.col == s2.col);
}

bool isOnSameDiag(const Square& s1, const Square& s2)
{
	return abs(s1.row - s2.row) == abs(s1.col - s2.col);
}

bool isKnightMove(const Square& s1, const Square& s2)
{
	int rowDiff = abs(s1.row - s2.row);
	int colDiff = abs(s1.col - s2.col);

	return (rowDiff == 1 && colDiff == 2) || (rowDiff == 2 && colDiff == 1);
}

int dist(const Square& s1, const Square& s2)
{
	int rowDiff = s1.row - s2.row;
	int colDiff = s1.col - s2.col;
	return static_cast<int>(sqrt(rowDiff*rowDiff + colDiff*colDiff));
}

std::string colorToString(const Color& color)
{
	return color == Color::WHITE ? "white" : "black";
}

std::string typeToString(const Type& type)
{
	switch (type) 
	{
	case Type::KING:
		return "King";
	case Type::ROOK:
		return "Rook";
	case Type::QUEEN:
		return "Queen";
	case Type::KNIGHT:
		return "Knight";
	case Type::PAWN:
		return "Pawn";
	case Type::BISHOP:
		return "Bishop";
	default:
		return "UNKNOWN";
	}
}