#pragma once
#include "ChessPiece.h"

class Pawn : public ChessPiece
{
	bool m_canPromote = false;
	bool m_hasMoved = false;
public:
	Pawn(const Color& color, const Square& square) : ChessPiece(color, square, Type::PAWN) {}
	bool canPromote() const { return m_canPromote; }
	void setCanPromote(bool promote) { m_canPromote = promote; }
	bool hasMoved() const { return m_hasMoved; }
	void setHasMoved(bool moved) {m_hasMoved = moved;}

	bool isValidMove(const Square& source, const Square& destination) const override;
	bool isValidCapture(const Square& source, const Square& destination) const override;
};