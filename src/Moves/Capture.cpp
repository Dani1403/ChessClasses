#include "Capture.h"
#include "../ChessGame.h"

bool Capture::checkValidity(ChessGame& game) const
{
	bool success = false;
	const std::shared_ptr<ChessBoard> board = game.getChessBoard();
	if (board->checkObstacles(m_source, m_destination) && (dynamic_cast<Knight*>(m_pieceToMove.get()) == nullptr))
		throw InvalidMove(OBSTACLE);
	if (m_pieceToMove->getColor() != game.getCurrentPlayer().getColor())
		throw InvalidMove(NOT_YOUR_COLOR);
	if (m_capturedPiece == nullptr)
		throw InvalidMove(DESTINATION_SQUARE_EMPTY);
	if (m_capturedPiece->getColor() == game.getCurrentPlayer().getColor())
		throw InvalidMove(YOUR_COLOR);
	if (!m_pieceToMove->isValidCapture(m_source, m_destination))
		throw InvalidMove(INVALID_CAPTURE);
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