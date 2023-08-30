#include "utilities.h"

bool isSquareValid(const Square& square)
{
	return square.row >= 0 && square.row <= 7 && square.col >= 0 && square.col <= 7;
}

Square algebraicToSquare(const std::string& notation)
{
	int col = notation[0] - 'a';
	int row = notation[1] - '1';
	return Square{ row, col };
}

std::string squareToAlgebraic(const Square& square)
{
	char col = 'a' + square.col;
	char row = '1' + square.row;
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

bool isDownwardDiag(const Square& s1, const Square& s2)
{
	return isOnSameDiag(s1, s2) && (s1.row < s2.row) && (s1.col > s2.col);
}

bool isKnightMove(const Square& s1, const Square& s2)
{
	int rowDiff = abs(s1.row - s2.row);
	int colDiff = abs(s1.col - s2.col);

	return (rowDiff == 1 && colDiff == 2) || (rowDiff == 2 && colDiff == 1);
}

int startRow(const Square& s1, const Square& s2)
{
	return std::min(s1.row, s2.row);
}

int endRow(const Square& s1, const Square& s2)
{
	return std::max(s1.row, s2.row);
}

int startCol(const Square& s1, const Square& s2)
{
	return std::min(s1.col, s2.col);
}

int endCol(const Square& s1, const Square& s2)
{
	return std::max(s1.col, s2.col);
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
		return "K";
	case Type::ROOK:
		return "R";
	case Type::QUEEN:
		return "Q";
	case Type::KNIGHT:
		return "Kn";
	case Type::PAWN:
		return "P";
	case Type::BISHOP:
		return "B";
	default:
		return "None";
	}
}