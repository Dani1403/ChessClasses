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

	/*
	 * check if a given color is in check
	 * @param color The color to check
	 * @return True if the color is in check, false otherwise
	 */
	bool isInCheck(const Color color);


	void appendMove(std::vector<std::shared_ptr<ChessMove>>&, std::shared_ptr<ChessMove>);

	void appendPromotion(std::vector<std::shared_ptr<ChessMove>>& moves, std::shared_ptr<Pawn> pawn, Square square);

  void appendCastle(std::vector<std::shared_ptr<ChessMove>>& moves);

	/*
	 *  Get all the possible moves for a given piece
	 * @param piece The piece to get the moves for
	 * @return A vector containing all the possible moves for the piece
	 */
	std::vector<std::shared_ptr<ChessMove>> getPossibleMovesForPiece(std::shared_ptr<ChessPiece> piece);

	bool checkPossibleMoves(const std::vector<std::shared_ptr<ChessMove>>& possibleMoves);

	/*
	 * check if a given color has a valid move
	 * @param color The color to check
	 * @return True if the color has a valid move, false otherwise
   */
	bool colorHasValidMove(const Color color);

	/*
	 * check if a given color is in checkmate
	 * @param color The color to check
	 * @return True if the color is in checkmate, false otherwise
	 */
	bool isInCheckmate(const Color color);

	/*
	 * check if a given color is in stalemate
	 * @param color The color to check
	 * @return True if the color is in stalemate, false otherwise
	 */
  bool isInStaleMate(const Color color);

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

};