#pragma once
#include "Player.h"
#include "ChessBoard.h"
#include "Moves/ChessMove.h"
#include "Moves/Capture.h"

class ChessGame
{
public:
	ChessGame();
	~ChessGame() {}

	void initBoard();

	std::shared_ptr<ChessBoard> getChessBoard() { return m_chessBoard; }

	//void play();

	void makeMove(std::shared_ptr<ChessMove> move);
	void undo();

	bool isInCheck(Color color);
	bool isInCheckmate(Color color);
	//bool isStaleMate();
	bool isGameOver();

private:
	std::shared_ptr<ChessBoard> m_chessBoard;
	std::vector<std::shared_ptr<ChessMove>> m_moves;
	std::vector<Player> m_players;
	Player m_currentPlayer;
};