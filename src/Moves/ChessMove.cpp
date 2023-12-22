#include "../ChessGame.h"
#include "ChessMove.h"

/*
* Checks if a regular move is valid
* checks for :
*	- the source square is not empty
*	- the color of the piece to move is the color of the current player
*	- there is a valid movement for this piece between source and destination
* - there is no piece at the destination
*	- there is no obstacle between the source and the destination
* - > raise the appropriate exception in case of invalid move
*
*	@param game : the game to check the move on
*	@return true if the move is valid, otherwise an exception is raised
*/
bool ChessMove::checkValidity(ChessGame& game) const
{
	const std::shared_ptr<ChessBoard> board = game.getChessBoard();
	if (board->getPieceAt(m_destination) != nullptr)
		throw InvalidMove(DESTINATION_SQUARE_NOT_EMPTY);
	if (!m_pieceToMove)
		throw InvalidMove(SOURCE_SQUARE_EMPTY);
	if (!m_pieceToMove->isValidMove(m_source, m_destination))
		throw InvalidMove(INVALID_MOVEMENT);
	if (board->checkObstacles(m_source, m_destination) && (dynamic_cast<Knight*>(m_pieceToMove.get()) == nullptr))
		throw InvalidMove(OBSTACLE);
	if (m_pieceToMove->getColor() != game.getCurrentPlayer().getColor())
		throw InvalidMove(NOT_YOUR_COLOR);
	return true;
}

/* Uses checkValidity to check if a move is possible
* @param game : the game to check the move on
* @return true if the move is possible, false otherwise
* Use this function when you don't want to handle the exceptions
*/
bool ChessMove::checkPossibleMove(ChessGame& game) const
{
	try
	{
		this->checkValidity(game);
	}
	catch (const InvalidMove&)
	{
		return false;
	}
	return true;
}

/*
* apply the move to the current game
*	@param game : the game to apply the move to
*	@return true if the move was applied, false otherwise
*/
bool ChessMove::execute(ChessGame& game) const
{
	const std::shared_ptr<ChessBoard> board = game.getChessBoard();
	board->movePiece(getPieceToMove(), getDest());
	const std::shared_ptr<Pawn> pawn = std::dynamic_pointer_cast<Pawn>(m_pieceToMove);
	if (pawn)
		pawn->setHasMoved(true);
	const std::shared_ptr<King> king = std::dynamic_pointer_cast<King>(m_pieceToMove);
	if (king)
		king->setHasMoved(true);
	const std::shared_ptr<Rook> rook = std::dynamic_pointer_cast<Rook>(m_pieceToMove);
	if (rook)
		rook->setHasMoved(true);
	return true;
}

/*
* undo the move on the current game
* @param game : the game to undo the move on
*/
void ChessMove::undo(ChessGame& game) const
{
	const std::shared_ptr<ChessBoard> board = game.getChessBoard();
	board->movePiece(getPieceToMove(), getSource());
}

/*
* equality operator for a move
* @param other : the move to compare to
* @return true if the moves are equal, false otherwise
*/
bool ChessMove::operator==(const ChessMove& other) const
{
	return (m_source == other.m_source) && (m_destination == other.m_destination) && (*m_pieceToMove == *other.m_pieceToMove);
}

/*
* @return a string containing all the information for a specific move
*/
std::string ChessMove::moveDescription() const
{
	return "Source: " + squareToAlgebraic(getSource()) + "\n" +
		"Destination: " + squareToAlgebraic(getDest()) + "\n" +
		"Piece To Move: \n" + getPieceToMove()->pieceDescription();
}

/*
* output operator for a move
* @param os : the output stream
* @param move : the move to output
* @return the output stream
*/
std::ostream& operator<<(std::ostream& os, const ChessMove& move)
{
	os << "Move: \n" + move.moveDescription();
	return os;
}