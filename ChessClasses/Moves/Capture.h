#pragma once
#include "../Pieces/ChessPiece.h"
#include "ChessMove.h"

class Capture : public ChessMove
{
	ChessPiece* m_capturedPiece;

public:
	Capture(const Square& source, const Square& destination, ChessPiece* capturedPiece) : 
		ChessMove(source, destination), m_capturedPiece(capturedPiece) {}

	void execute(ChessGame&) override;
	void undo(ChessGame&) override;
};

