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