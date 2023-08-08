#pragma once
#include "ChessPiece.h"

class Bishop : public ChessPiece
{
public:
	Bishop(const Color& color, const Square& square) : ChessPiece(color, square, Type::BISHOP) {}

	bool isValidMove(const Square& source, const Square& destination) const override;
};