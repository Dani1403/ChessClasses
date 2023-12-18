#include "EnPassant.h"
#include "../ChessGame.h"


bool EnPassant::checkValidity(ChessGame& game) const
{
  const std::shared_ptr<Pawn> pawnToMove = std::dynamic_pointer_cast<Pawn>(m_pieceToMove);
  if (pawnToMove->getColor() == game.getCurrentPlayer().getColor())
      throw InvalidMove(YOUR_COLOR);
  if (!pawnToMove)
    throw InvalidMove(NOT_PAWN);
  if (pawnToMove->getSquare().row != pawnToMove->rowForEnPassant())
    throw InvalidMove(NOT_EN_PASSANT_ROW);
  if (!isValidColumnForEnPassant(m_source.col, m_destination.col))
    throw InvalidMove(NOT_EN_PASSANT_COL);
  if (pawnToMove->getColor() != game.getCurrentPlayer().getColor())
    throw InvalidMove(NOT_YOUR_COLOR);
  const std::shared_ptr<ChessMove> lastMove = game.getLastMove();
  if (!lastMove)
    throw InvalidMove(NO_LAST_MOVE);
  if (!std::dynamic_pointer_cast<Pawn>(lastMove->getPieceToMove()))
	   throw InvalidMove(LAST_MOVE_NOT_PAWN);
  if (abs(lastMove->getDest().row - lastMove->getSource().row) != 2)
    throw InvalidMove(INVALID_LAST_MOVE);
	return false;
}

bool EnPassant::execute(ChessGame& game) const
{
	return Capture::execute(game);
}

void EnPassant::undo(ChessGame& game) const
{
	Capture::undo(game);
}