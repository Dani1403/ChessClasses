#include "Castle.h"
#include "../ChessGame.h"

bool Castle::checkValidity(ChessGame& game) const
{
  const std::shared_ptr<ChessBoard> board = game.getChessBoard();
  if (!m_pieceToMove)
      throw InvalidMove(SOURCE_SQUARE_EMPTY);
  if (board->checkObstacles(m_source, m_destination) && (dynamic_cast<Knight*>(m_pieceToMove.get()) == nullptr))
    throw InvalidMove(OBSTACLE);
  if (m_rookToMove->hasMoved())
    throw InvalidMove(INVALID_CASTLE_ROOK);
  const std::shared_ptr<King> king = std::dynamic_pointer_cast<King>(m_pieceToMove);
  if (king->hasMoved())
    throw InvalidMove(INVALID_CASTLE_KING);
  if (game.isInCheck(game.getCurrentPlayer().getColor()))
    throw InvalidMove(INVALID_CASTLE_CHECK);
  return true;
}

bool Castle::execute(ChessGame& game) const
{
  m_kingMove.execute(game);
  m_rookMove.execute(game);
  return true;
}

void Castle::undo(ChessGame& game) const
{
  m_kingMove.undo(game);
  m_rookMove.undo(game);
}

std::string Castle::moveDescription() const
{
  return "Castle: \n" + 
    m_kingMove.moveDescription() + "\n" + m_rookMove.moveDescription();
}