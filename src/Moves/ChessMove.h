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

	/*
	* return a string containing all the information for a specific move
	*/
	virtual std::string moveDescription() const;

	/* Getters */
	Square getSource() const { return m_source; }
	Square getDest() const { return m_destination; }
	std::shared_ptr<ChessPiece> getPieceToMove() const { return m_pieceToMove; }

	/* Setters */
	void setSource(const Square& newSource) { m_source = newSource; }
	void setDest(const Square& newDestination) { m_destination = newDestination; }
	void setPieceToMove(std::shared_ptr<ChessPiece> newPieceToMove) { m_pieceToMove = newPieceToMove; }

	/*
	* checks if a regular move is valid
	* checks for :
	*	- color of the piece to move is the color of the current player
	*	- there is a valid movement for this piece between source and destination
	* - there is no piece at the destination
	*	- there is no obstacle between the source and the destination
	*	- the move doesnt end up with the current player being in check
	* 
	* - > raise the appropriate exception in case of invalid move
	*/
	virtual void checkValidity(ChessGame& game) const;

	/*
	* apply the move to the current game
	*/
	virtual bool execute(ChessGame& game) const;

	virtual void undo(ChessGame& game) const;

protected:
	Square m_source, m_destination;
	std::shared_ptr<ChessPiece> m_pieceToMove;
};

std::ostream& operator<<(std::ostream& os, const ChessMove& move);
