#include "EnPassant.h"
#include "../ChessGame.h"

bool EnPassant::execute(ChessGame& game) const 
{
	return Capture::execute(game);
}

void EnPassant::undo(ChessGame& game) const
{
	Capture::undo(game);
}