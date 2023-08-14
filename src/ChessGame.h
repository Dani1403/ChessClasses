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

	void init();
	void play();

	void makeMove(ChessMove* move);
	void undo();

	bool isInCheck(Color color);
	bool isInCheckmate(Color color);
	bool isStaleMate();
	bool isGameOver();

private:
	std::unique_ptr<ChessBoard> m_chessBoard;
	std::vector<ChessMove*> m_moves;
};