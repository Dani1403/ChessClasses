#include "Castle.h"
#include "../ChessGame.h"

bool Castle::checkValidity(ChessGame& game) const
{
  const std::shared_ptr<ChessBoard> board = game.getChessBoard();
  if (board->checkObstacles(m_source, m_destination) && (dynamic_cast<Knight*>(m_pieceToMove.get()) == nullptr))
    throw InvalidMove(OBSTACLE);
  if (m_rookToMove->hasMoved())
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