#pragma once
#include "ChessPiece.h"

class King : public ChessPiece
{
	bool m_hasMoved = false;

public:
	King(const Color& color, const Square& square) : ChessPiece(color, square, Type::KING) {}
	bool hasMoved() const { return m_hasMoved; }
	void setHasMoved(bool moved) { m_hasMoved = moved; }

	bool isValidMove(const Square& source, const Square& destination) const override;
};