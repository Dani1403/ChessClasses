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
* @param game : the game to check the move on
* @return an InvalidCause enum value
* @override the ChessMove::checkValidity() function
*/
InvalidCause Capture::checkValidity(ChessGame& game) const
{
	const std::shared_ptr<ChessBoard> board = game.getChessBoard();
	if (!m_pieceToMove)
		return InvalidCause::SOURCE_SQUARE_EMPTY;
	if (board->checkObstacles(m_source, m_destination) && (dynamic_cast<Knight*>(m_pieceToMove.get()) == nullptr))
		return InvalidCause::OBSTACLE;
	if (m_pieceToMove->getColor() != game.getCurrentPlayer().getColor())
		return InvalidCause::NOT_YOUR_COLOR;
	if (m_capturedPiece == nullptr)
		return InvalidCause::DESTINATION_SQUARE_EMPTY;
	if (m_capturedPiece->getColor() == game.getCurrentPlayer().getColor())
		return InvalidCause::YOUR_COLOR;
	if (!m_pieceToMove->isValidCapture(m_source, m_destination))
		return InvalidCause::INVALID_CAPTURE;
	return InvalidCause::SUCCESS;
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