#pragma once
#include "Capture.h"
#include "../Pieces/Pawn.h"

class EnPassant : public Capture
{
public:
	EnPassant(const Square& source, Pawn* pawnToMove, Pawn* pawnToCapture) :
		Capture(source, {source.col + 1, source.row + 1}, pawnToMove, pawnToCapture)
	{}

	bool execute(ChessGame& game) const override;
	void undo(ChessGame& game) const override;
};

