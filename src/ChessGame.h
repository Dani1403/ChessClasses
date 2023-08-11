#pragma once

#include "ChessBoard.h"

class ChessGame
{
public:
	ChessGame() {}
	~ChessGame() {}
	ChessBoard* getChessBoard() { return m_chessBoard.get(); }
private:
	std::unique_ptr<ChessBoard> m_chessBoard;
};