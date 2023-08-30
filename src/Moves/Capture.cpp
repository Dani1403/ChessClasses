#include "Capture.h"
#include "../ChessGame.h"

void Capture::checkValidity(ChessGame& game) const
{
	std::shared_ptr<ChessBoard> board = game.getChessBoard();
	std::shared_ptr<ChessPiece> piece = board->getPieceAt(m_destination);
	try
	{
		ChessMove::checkValidity(game);
	}
	catch (const InvalidMove& invalid)
	{
		if (invalid.message() != "There is already a piece at the destination" &&
			invalid.message() != "Invalid movement for this piece")
			throw invalid;
	}
	if (piece == nullptr)
		throw InvalidMove("There is no piece at the destination");
	if (piece->getColor() == game.getCurrentPlayer().getColor())
		throw InvalidMove("The piece to capture is of your color");
}

bool Capture::execute(ChessGame& game) const 
{
	std::shared_ptr<ChessBoard> board = game.getChessBoard();
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