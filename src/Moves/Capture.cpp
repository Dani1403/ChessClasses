#include "Capture.h"
#include "../ChessGame.h"

bool Capture::checkValidity(ChessGame& game) const
{
	bool success = false;
	std::shared_ptr<ChessBoard> board = game.getChessBoard();
	try
	{
		success = ChessMove::checkValidity(game);
	}
	catch (const InvalidMove& invalid)
	{
		if (invalid.getCause() != std::string("There is already a piece at the destination") &&
			invalid.getCause() != std::string("Invalid movement for this piece"))
			throw invalid;
	}
	if (m_capturedPiece == nullptr)
		throw InvalidMove("There is no piece at the destination");
	if (m_capturedPiece->getColor() == game.getCurrentPlayer().getColor())
		throw InvalidMove("The piece to capture is of your color");
	if (!m_pieceToMove->isValidCapture(m_source, m_destination))
		throw InvalidMove("This is not a valid capture for this piece");
	return success;
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