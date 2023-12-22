#include "../ChessGame.h"
#include "EnPassant.h"

/* Apply the move to the current game
* @param game : the game to apply the move to
* @return true if the move was applied, false otherwise
* @override the Capture::execute() function
*/
bool EnPassant::execute(ChessGame& game) const
{
	return Capture::execute(game);
}

/*
* Undo the move on the current game
* @param game : the game to undo the move on
* @override the Capture::undo() function
*/
void EnPassant::undo(ChessGame& game) const
{
	Capture::undo(game);
}