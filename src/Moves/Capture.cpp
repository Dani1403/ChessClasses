#include "../ChessGame.h"
#include "Capture.h"

/*
* Checks if a capture move is valid
* Checks for :
* - the source square is not empty
* - the color of the piece to move is the color of the current player
* - there is a valid capture for this piece between source and destination
* - there is a piece at the destination
* - there is no obstacle between the source and the destination
* - > raise the appropriate exception in case of invalid move
*
* @param game : the game to check the move on
* @return true if the move is valid, otherwise an exception is raised
* @override the ChessMove::checkValidity() function
*/
bool Capture::checkValidity(ChessGame& game) const
{
	const std::shared_ptr<ChessBoard> board = game.getChessBoard();
	if (!m_pieceToMove)
		throw InvalidMove(SOURCE_SQUARE_EMPTY);
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
	return true;
}

/*
* Apply the move to the current game
* @param game : the game to apply the move to
* @return true if the move was applied, false otherwise
* @override the ChessMove::execute() function
*/
bool Capture::execute(ChessGame& game) const
{
	const std::shared_ptr<ChessBoard> board = game.getChessBoard();
	board->removePiece(getCapturedPiece());
	board->movePiece(getPieceToMove(), getDest());
	return true;
}

/*
* Undo the move on the current game
* @param game : the game to undo the move on
* @override the ChessMove::undo() function
*/
void Capture::undo(ChessGame& game) const
{
	const std::shared_ptr<ChessBoard> board = game.getChessBoard();
	board->movePiece(getPieceToMove(), getSource());
	board->addPiece(getCapturedPiece());
}

/*
* @return a string describing the move
* @override the ChessMove::moveDescription() function
*/
std::string Capture::moveDescription() const
{
	return ChessMove::moveDescription() + "\n" +
		"Captured piece: " + getCapturedPiece()->pieceDescription();
}