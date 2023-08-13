#pragma once
#include "ChessMove.h"
#include "../Pieces/Pawn.h"

class Promotion : public ChessMove
{
public:
	Promotion(const Square& source, const Square& destination, Pawn* pawnToPromote, ChessPiece* newPiece) :
		ChessMove(source, destination, pawnToPromote), m_newPiece(newPiece)
	{}

	ChessPiece* getNewPiece() const { return m_newPiece; }

	bool execute(ChessGame& game) const override;
	void undo(ChessGame& game) const override;

private:
	ChessPiece* m_newPiece;
};

