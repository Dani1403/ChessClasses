#include "ChessMove.h"
#include "../ChessGame.h"

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


bool ChessMove::checkPossibleMove(ChessGame& game) const
{
	try
	{
		this->checkValidity(game);
	} catch (const InvalidMove&)
	{
		return false;
	}
	return true;
}

bool ChessMove::execute(ChessGame& game) const 
{
	std::shared_ptr<ChessBoard> board = game.getChessBoard();
	board->movePiece(getPieceToMove(), getDest());
	if (dynamic_cast<Pawn*>(m_pieceToMove.get()) != nullptr)
		dynamic_cast<Pawn*>(m_pieceToMove.get())->setHasMoved(true);
	if (dynamic_cast<King*>(m_pieceToMove.get()) != nullptr)
    dynamic_cast<King*>(m_pieceToMove.get())->setHasMoved(true);
	if (dynamic_cast<Rook*>(m_pieceToMove.get()) != nullptr)
    dynamic_cast<Rook*>(m_pieceToMove.get())->setHasMoved(true);
	return true;
}

void ChessMove::undo(ChessGame& game) const 
{
	std::shared_ptr<ChessBoard> board = game.getChessBoard();
	board->movePiece(getPieceToMove(), getSource());
}

bool ChessMove::operator==(const ChessMove& other) const
{
	return (m_source == other.m_source) && (m_destination == other.m_destination) && (*m_pieceToMove == *other.m_pieceToMove);
}

std::string ChessMove::moveDescription() const
{
	return "Source: " + squareToAlgebraic(getSource()) + "\n" + 
		"Destination: " + squareToAlgebraic(getDest()) + "\n" + 
		"Piece To Move: \n" + getPieceToMove()->pieceDescription();
}

std::ostream& operator<<(std::ostream& os, const ChessMove& move)
{
	os << "Move: \n" + move.moveDescription();
	return os;
}