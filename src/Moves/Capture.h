#pragma once
#include "ChessMove.h"

class Capture : public ChessMove
{
public:
	Capture(const Square& source, const Square& destination, ChessPiece* pieceToMove, ChessPiece* capturedPiece) : 
		ChessMove(source, destination, pieceToMove), m_capturedPiece(capturedPiece) {}

	ChessPiece* getCapturedPiece() const { return m_capturedPiece; }

	virtual bool execute(ChessGame&) const override;
	virtual void undo(ChessGame&) const override;
private:
	ChessPiece* m_capturedPiece;
};

