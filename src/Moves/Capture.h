#pragma once
#include "ChessMove.h"

class Capture : public ChessMove
{
public:
	Capture(const Square& source, const Square& destination, ChessPiece* pieceToMove, ChessPiece* capturedPiece) : 
		ChessMove(source, destination, pieceToMove), m_capturedPiece(capturedPiece) {}

	bool execute(ChessGame&) const override;
	void undo(ChessGame&) const override;
private:
	ChessPiece* m_capturedPiece;
};

