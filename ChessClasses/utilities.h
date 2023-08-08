#pragma once

#include <string>

enum class Color { NONE = 0, WHITE, BLACK };

enum class Type
{
	NONE = 0, PAWN, KNIGHT, BISHOP, QUEEN, ROOK, KING
};

struct Square
{
	int row, col;
};

bool isSquareValid(const Square& square);

Square algebraicToSquare(const std::string& notation);

std::string colorToString(const Color& color);

std::string typeToString(const Type& type);

std::string squareToAlgebraic(const Square& square);
