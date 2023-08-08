#pragma once
#include "../ChessGame.h"
#include "../utilities.h"

class ChessMove
{
protected:
	Square m_source, m_destination;
public:
	ChessMove(const Square& source, const Square& destination) :
		m_source(source), m_destination(destination) {}
	virtual ~ChessMove() = default;

	virtual void execute(ChessGame&) = 0;
	virtual void undo(ChessGame&) = 0;
};