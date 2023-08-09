#pragma once

#include "ChessBoard.h"

class ChessGame
{
	std::unique_ptr<ChessBoard> m_chessBoard;
public:
	ChessGame() {}
	~ChessGame() {}
	ChessBoard* getChessBoard() { return m_chessBoard.get(); }
};