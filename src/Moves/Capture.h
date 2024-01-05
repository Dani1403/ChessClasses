#pragma once
#include "ChessMove.h"

class Capture : public ChessMove
{
public:
	/* Constructor*/
	Capture(const Square& source, const Square& destination, std::shared_ptr<ChessPiece> pieceToMove, std::shared_ptr<ChessPiece> capturedPiece) :
		ChessMove(source, destination, pieceToMove), m_capturedPiece(capturedPiece) {}

	/* Getters and Setters */

	std::shared_ptr<ChessPiece> getCapturedPiece() const { return m_capturedPiece; }

	/*
	* Checks if a capture move is valid
	* Checks for :
	* - the source square is not empty
	* - the color of the piece to move is the color of the current player
	* - there is a valid capture for this piece between source and destination
	* - there is a piece at the destination
	* - there is no obstacle between the source and the destination
	*
	* @param game : the game to check the move on
	* @return an InvalidCause enum value
	* @override the ChessMove::checkValidity() function
	*/
	virtual InvalidCause checkValidity(ChessGame& game) const override;

	/*
	* Apply the move to the current game
	* @param game : the game to apply the move to
	* @return true if the move was applied, false otherwise
	* @override the ChessMove::execute() function
	*/
	virtual bool execute(ChessGame& game) const override;

	/*
	* Undo the move on the current game
	* @param game : the game to undo the move on
	* @override the ChessMove::undo() function
	*/
	virtual void undo(ChessGame& game) const override;

	/*
	* @return a string describing the move
	* @override the ChessMove::moveDescription() function
	*/
	std::string moveDescription() const override;

private:
	std::shared_ptr<ChessPiece> m_capturedPiece;
};

