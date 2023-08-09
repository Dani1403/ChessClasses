#pragma once
#include "../utilities.h"

class ChessPiece;
class ChessGame;

class ChessMove
{
protected:
	Square m_source, m_destination;
	ChessPiece* m_pieceToMove;
public:
	ChessMove(const Square& source, const Square& destination, ChessPiece* pieceToMove) :
		m_source(source), m_destination(destination), m_pieceToMove(pieceToMove) {}
	virtual ~ChessMove() = default;

	Square getSource() const { return m_source; }
	Square getDest() const { return m_destination; }
	ChessPiece* getPieceToMove() const { return m_pieceToMove; }

	void setSource(const Square& newSource) { m_source = newSource; }
	void setDest(const Square& newDestination) { m_destination = newDestination; }
	void setPieceToMove(ChessPiece* newPieceToMove) { m_pieceToMove = newPieceToMove; }

	virtual bool execute(ChessGame& game) const = 0;
	virtual void undo(ChessGame& game) const = 0;
};