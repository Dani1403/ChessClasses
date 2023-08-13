#pragma once
#include "ChessPiece.h"

class Queen : ChessPiece
{
public:
	Queen(const Color& color, const Square& square) : ChessPiece(color, square, Type::QUEEN) {}

	bool isValidMove(const Square& source, const Square& destination) const override;
};