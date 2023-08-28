#pragma once
#include "ChessMove.h"
#include "../Pieces/Pawn.h"

class Promotion : public ChessMove
{
public:
	Promotion(const Square& source, const Square& destination, std::shared_ptr<Pawn> pawnToPromote, std::shared_ptr<ChessPiece> newPiece) :
		ChessMove(source, destination, pawnToPromote), m_newPiece(newPiece)
	{}

	std::string moveDescription() const override;

	std::shared_ptr<ChessPiece> getNewPiece() const { return m_newPiece; }

	bool execute(ChessGame& game) const override;
	void undo(ChessGame& game) const override;

private:
	std::shared_ptr<ChessPiece> m_newPiece;
};

