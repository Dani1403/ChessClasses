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
	~ChessGame() = default;
	ChessGame(const ChessGame& other) = delete;
	ChessGame& operator=(const ChessGame& other) = delete;

	/*
	 * Initializes the board with the pieces in their starting positions
	 */
	void initBoard();

	/* Getters */
	std::shared_ptr<ChessBoard> getChessBoard() const { return m_chessBoard; }
	const Player& getCurrentPlayer() const { return m_currentPlayer; }

	////////// Main loop functions and move logic

	/*
	 * Checks if the move is valid and if it is, makes the move
	 * @param move The move to be made
	 * @return True if the move was made, false otherwise
	 */
	bool makeMove(std::shared_ptr<ChessMove> move);

	/*
	 * Undoes the last move
	 */
	void undo();

	/*
	 * moves the game to the next player
	 */
	void moveToNextPlayer();

	/*
	 * Play a turn for the current player
	 */
	void playerTurn();

	/*
	 * Play the game
	 */
	void play();

	//////////////////// Status Logic

	/*
	 * check if a given color is in check
	 * @param color The color to check
	 * @return True if the color is in check, false otherwise
   */
	bool isInCheck(const Color color);

	/*
	 * check if a given color is in checkmate
   * @param color The color to check
   * @return True if the color is in checkmate, false otherwise
   */
	bool isInCheckmate(const Color color);


	//bool isStaleMate();

	/*
	 * check if the game is over
   * @return True if the game is over, false otherwise
   */
	bool isGameOver();

private:
	std::shared_ptr<ChessBoard> m_chessBoard;
	std::vector<std::shared_ptr<ChessMove>> m_moves;
	std::list<Player> m_players;
	Player m_currentPlayer;

	bool checkPossibleCapture(std::shared_ptr<Capture> capture);
};