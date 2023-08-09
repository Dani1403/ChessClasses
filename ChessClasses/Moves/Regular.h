#pragma once
#include "ChessMove.h"
#include "../ChessGame.h"

class Regular : public ChessMove
{
public:
	bool execute(ChessGame& game) const override;
	void undo(ChessGame& game) const override;
};

