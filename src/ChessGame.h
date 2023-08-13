#pragma once

#include "ChessBoard.h"
#include "Moves/ChessMove.h"
#include "Moves/Capture.h"

class ChessGame
{
public:
	ChessGame() {}
	~ChessGame() {}
	ChessBoard* getChessBoard() { return m_chessBoard.get(); }
	bool isInCheck(Color color);
private:
	std::unique_ptr<ChessBoard> m_chessBoard;
};