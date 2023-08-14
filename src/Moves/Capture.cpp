#include "Capture.h"
#include "../ChessGame.h"

bool Capture::execute(ChessGame& game) const 
{
	ChessBoard* board = game.getChessBoard();
	board->removePiece(getCapturedPiece());
	board->movePiece(getPieceToMove(), getDest());
	return true; 
}

void Capture::undo(ChessGame& game) const
{
	ChessMove::undo(game);
	game.getChessBoard()->addPiece(getCapturedPiece());
}

std::string Capture::moveDescription() const
{
	return ChessMove::moveDescription() + "\n" +
		"Captured piece: " + getCapturedPiece()->pieceDescription();
}