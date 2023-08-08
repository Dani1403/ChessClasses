#pragma once
#include "ChessPiece.h"

class Knight : public ChessPiece
{
public:
	Knight(const Color& color, const Square& square) : ChessPiece(color, square, Type::KNIGHT) {}

	bool isValidMove(const Square& source, const Square& destination) const override;
};