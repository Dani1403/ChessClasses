#pragma once
#include "ChessMove.h"

class Capture : public ChessMove
{
public:
	Capture(const Square& source, const Square& destination, std::shared_ptr<ChessPiece> pieceToMove, std::shared_ptr<ChessPiece> capturedPiece) : 
		ChessMove(source, destination, pieceToMove), m_capturedPiece(capturedPiece) {}

	std::string moveDescription() const override;

	std::shared_ptr<ChessPiece> getCapturedPiece() const { return m_capturedPiece; }

	virtual void checkValidity(ChessGame& game) const override;
	virtual bool execute(ChessGame& game) const override;
	virtual void undo(ChessGame& game) const override;
private:
	std::shared_ptr<ChessPiece> m_capturedPiece;
};

