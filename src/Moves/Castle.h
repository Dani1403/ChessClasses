#pragma once
#include "ChessMove.h"
#include "../Pieces/Rook.h"

class Castle : public ChessMove
{
public:
	Castle(const Square& source, const Square& destination, ChessPiece* kingToMove, Rook* rookToMove):
		ChessMove(source, destination, kingToMove), m_rookToMove(rookToMove) {}

	Rook* getRookToMove() const { return m_rookToMove; }

	bool execute(ChessGame& game) const;
	void undo(ChessGame& game) const;
private:
	Rook* m_rookToMove;
};

