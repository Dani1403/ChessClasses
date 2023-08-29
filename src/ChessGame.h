#pragma once
#include "Player.h"
#include "ChessBoard.h"
#include "Moves/ChessMove.h"
#include "Moves/Capture.h"

class ChessGame
{
public:
	/* Constructor and destructors */
	ChessGame();
	~ChessGame() {}
	void initBoard();

	/* Getters */
	std::shared_ptr<ChessBoard> getChessBoard() const { return m_chessBoard; }
	const Player& getCurrentPlayer() const { return m_currentPlayer; }



	/* Main loop functions and move logic*/
		/* Move Logic */
	void makeMove(std::shared_ptr<ChessMove> move);
	void undo();

	//void play();
	void moveToNextPlayer();

	/* Status Logic */
	bool isInCheck(Color color);
	bool isInCheckmate(Color color);
	//bool isStaleMate();
	bool isGameOver();

private:
	std::shared_ptr<ChessBoard> m_chessBoard;
	std::vector<std::shared_ptr<ChessMove>> m_moves;
	std::list<Player> m_players;
	Player m_currentPlayer;
};