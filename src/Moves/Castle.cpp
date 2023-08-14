#include "Castle.h"
#include "../ChessGame.h"

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