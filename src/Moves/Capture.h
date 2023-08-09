#pragma once
#include "../Pieces/ChessPiece.h"
#include "ChessMove.h"

class Capture : public ChessMove
{
	ChessPiece* m_capturedPiece;

public:
	Capture(const Square& source, const Square& destination, ChessPiece* pieceToMove, ChessPiece* capturedPiece) : 
		ChessMove(source, destination, pieceToMove), m_capturedPiece(capturedPiece) {}

	bool execute(ChessGame&) const override;
	void undo(ChessGame&) const override;
};

