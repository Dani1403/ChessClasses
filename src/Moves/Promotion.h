#pragma once
#include "../Pieces/Pawn.h"
#include "ChessMove.h"

class Promotion : public ChessMove
{
public:

	/*Constructor*/
	Promotion(const Square& source, const Square& destination, std::shared_ptr<Pawn> pawnToPromote, std::shared_ptr<ChessPiece> newPiece) :
		ChessMove(source, destination, pawnToPromote), m_newPiece(newPiece)
	{}

	/* Getters and Setters */
	std::shared_ptr<ChessPiece> getNewPiece() const { return m_newPiece; }

	/*
	* Checks if a promotion move is valid
	* Uses the checkValidity() function from the ChessMove class
	* @param game : the game to check the move on
	* @return an InvalidCause enum value
	* @override the ChessMove::checkValidity() function
	*/
	InvalidCause checkValidity(ChessGame& game) const override;

	/*
	* Apply the move to the current game
	* @param game : the game to apply the move to
	* @return true if the move was applied, false otherwise
	* @override the ChessMove::execute() function
	*/
	bool execute(ChessGame& game) const override;

	/*
	* Undo the move on the current game
	* @param game : the game to undo the move on
	* @override the ChessMove::undo() function
	*/
	void undo(ChessGame& game) const override;

	/*
	* @return a string describing the move
	*	@override the ChessMove::moveDescription() function
	*/
	std::string moveDescription() const override;

private:
	std::shared_ptr<ChessPiece> m_newPiece;
};

