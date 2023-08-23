#include "ChessMove.h"
#include "../ChessGame.h"

bool ChessMove::execute(ChessGame& game) const 
{
	std::shared_ptr<ChessBoard> board = game.getChessBoard();
	board->movePiece(getPieceToMove(), getDest());
	return true;
}

void ChessMove::undo(ChessGame& game) const 
{
	std::shared_ptr<ChessBoard> board = game.getChessBoard();
	board->movePiece(getPieceToMove(), getSource());
}

std::string ChessMove::moveDescription() const
{
	return "Source: " + squareToAlgebraic(getSource()) + "\n" + 
		"Destination: " + squareToAlgebraic(getDest()) + "\n" + 
		"Piece To Move: " + getPieceToMove()->pieceDescription();
}

std::ostream& operator<<(std::ostream& os, const ChessMove& move)
{
	os << "Move: " + move.moveDescription();
	return os;
}