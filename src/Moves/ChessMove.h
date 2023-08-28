#pragma once
#include "../utilities.h"
#include "../Pieces/ChessPiece.h"

class ChessGame;

class ChessMove
{
public:
	ChessMove(const Square& source, const Square& destination, std::shared_ptr<ChessPiece> pieceToMove) :
		m_source(source), m_destination(destination), m_pieceToMove(pieceToMove) {}
	virtual ~ChessMove() = default;

	virtual std::string moveDescription() const;

	Square getSource() const { return m_source; }
	Square getDest() const { return m_destination; }
	std::shared_ptr<ChessPiece> getPieceToMove() const { return m_pieceToMove; }

	void setSource(const Square& newSource) { m_source = newSource; }
	void setDest(const Square& newDestination) { m_destination = newDestination; }
	void setPieceToMove(std::shared_ptr<ChessPiece> newPieceToMove) { m_pieceToMove = newPieceToMove; }

	virtual bool isValid(ChessGame& game) const;
	virtual bool execute(ChessGame& game) const;
	virtual void undo(ChessGame& game) const;

protected:
	Square m_source, m_destination;
	std::shared_ptr<ChessPiece> m_pieceToMove;
};

std::ostream& operator<<(std::ostream& os, const ChessMove& move);
