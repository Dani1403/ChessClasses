#pragma once
#include "ChessBoard.h"
#include "Moves/Capture.h"
#include "Moves/ChessMove.h"
#include "Player.h"

class ChessGame
{
public:
	/* Constructor and destructors */

	ChessGame()
	{
		auto image = sf::Image();
		if (image.loadFromFile("src/img/Chess_kdt45.png"))
		{
			m_window.setIcon(ICON_SIZE, ICON_SIZE, image.getPixelsPtr());
			m_inputWindow.setIcon(ICON_SIZE, ICON_SIZE, image.getPixelsPtr());
		}
		m_chessBoard = std::make_shared<ChessBoard>();
	}

	~ChessGame() = default;
	ChessGame(const ChessGame& other) = delete;
	ChessGame& operator=(const ChessGame& other) = delete;

	/* Getters */

	std::shared_ptr<ChessBoard> getChessBoard() const { return m_chessBoard; }
	const Player& getCurrentPlayer() const { return m_currentPlayer; }

	/*
	* Initializes the players with their names and colors
	*/
	void initPlayers();

	/*
	* Initializes the board with the pieces in their starting positions
	*/
	void initBoard();

	/*
	* Checks if a square is attacked by a given color
	* @param square The square to check
	* @param color The color of the piece that is possibly attacking
	*/
	bool isSquareAttacked(const Square square, const Color color);

	/*
	* check if a given color is in check
	* @param color The color to check
	* @return True if the color is in check, false otherwise
	*/
	bool isInCheck(const Color color);

	/*
	*  Get all the possible moves for a given piece
	* @param piece The piece to get the moves for
	* @return A vector containing all the possible moves for the piece
	*/
	std::vector<std::shared_ptr<ChessMove>> getPossibleMovesForPiece(std::shared_ptr<ChessPiece> piece);

	/*
	* for all possible moves, check if the king is still in check after the move
	* @param possibleMoves The possible moves to check
	* @param color The color to check
	* @return true if the king is not in check after at least one move, false otherwise
	*/
	bool checkPossibleMoves(const std::vector<std::shared_ptr<ChessMove>>& possibleMoves, Color color);

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
	* @return a string representing the issue of the game if it's over, empty string otherwise
	*/
	std::string isGameOver();

	/*
	* Checks if the move is valid and if it is, makes the move
	* @param move The move to be made
	* @return an InvalidCause enum value
	*/
	InvalidCause makeMove(const std::shared_ptr<ChessMove>& move);

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
	*	-> start the timer of the current player
	*	-> get the move from the player in a separate thread
	*	-> wait for the move to be ready
	*	-> render the window while waiting
	*	-> make the move
	*	-> stop the timer of the current player
	*/
	void playerTurn();

	/*
	* Render the timers of the players to the window
	*/
	void renderTimers() const;

	/*
	* Play the game
	*/
	void play();

	/*
	* Render the game to the window
	*	-> clear the window
	*	-> render the board
	*	-> render the timers
	*	-> display the window
	*/
	void renderWindow();

private:
	sf::RenderWindow& m_window = sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Chess++");
	sf::RenderWindow& m_inputWindow = sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Chess++ input");
	std::shared_ptr<ChessBoard> m_chessBoard;
	std::vector<std::shared_ptr<ChessMove>> m_moves;
	std::list<Player> m_players;
	Player m_currentPlayer;

	/*
	* Initializes a player with a name and a color
	* @param player The player to initialize
	* @param color The color of the player
	*/
	void initPlayer(Player& player, const Color color);

	/*
	* Checks if a given move can be made using its checkPossibleMove function
	* @param move The move to check
	* @param possibleMoves a vector of possible moves
	* if the move is valid, append it to the vector of possible moves
	*/
	void appendMove(std::vector<std::shared_ptr<ChessMove>>&, std::shared_ptr<ChessMove>);

	/*
	* Creates a regular move from an existing piece and a destination square
	* @param moves a vector of possible moves
	* @param piece The piece to move
	* @param destSquare The destination square
	* if the move is valid, append it to the vector of possible moves
	*/
	void appendRegular(std::vector<std::shared_ptr <ChessMove>>& moves, std::shared_ptr<ChessPiece> piece, Square destSquare);

	/*
	* Creates a capture move from an existing piece, a captured piece and a destination square
	* @param moves a vector of possible moves
	* @param piece The piece to move
	* @param captured The piece to capture
	* @param destSquare The destination square
	* if the capture is valid, append it to the vector of possible moves
	*/
	void appendCapture(std::vector<std::shared_ptr <ChessMove>>& moves, std::shared_ptr<ChessPiece> piece, std::shared_ptr<ChessPiece> captured, Square destSquare);

	/*
	* Creates a promotion move from an existing pawn and a destination square
	* @param moves a vector of possible moves
	* @param pawn The pawn to move
	* @param destSquare The destination square
	* if the promotion is valid, append it to the vector of possible moves
	*/
	void appendPromotion(std::vector<std::shared_ptr<ChessMove>>& moves, std::shared_ptr<Pawn> pawn, Square destSquare);

	/*
	* Create two castle moves from an existing king
	* @param moves a vector of possible moves
	* if the castle is valid, append it to the vector of possible moves
	*/
	void appendCastle(std::vector<std::shared_ptr<ChessMove>>& moves);
};