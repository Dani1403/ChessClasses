#pragma once
#include "../Pieces/Pawn.h"
#include "Capture.h"

class EnPassant : public Capture
{
public:
	/* Constructor */
	EnPassant(const Square& source, std::shared_ptr<Pawn> pawnToMove, std::shared_ptr<Pawn> pawnToCapture) :
		Capture(source, { source.col + 1, source.row + 1 }, pawnToMove, pawnToCapture)
	{}

	/* Apply the move to the current game
	* @param game : the game to apply the move to
	* @return true if the move was applied, false otherwise
	* @override the Capture::execute() function
	*/
	bool execute(ChessGame& game) const override;

	/*
	* Undo the move on the current game
	* @param game : the game to undo the move on
	* @override the Capture::undo() function
	*/
	void undo(ChessGame& game) const override;
};

