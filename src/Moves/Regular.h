#pragma once
#include "ChessMove.h"

class Regular : public ChessMove
{
public:
	bool execute(ChessGame& game) const override;
	void undo(ChessGame& game) const override;
};

