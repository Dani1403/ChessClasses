#pragma once
#include "Moves/Capture.h"
#include "Moves/Castle.h"
#include "Moves/Promotion.h"
#include "Timer.h"
#include "utilities.h"


class ChessMove;
class ChessBoard;
class ChessGame;

class Player
{
public:
	/* Constructor and destructors*/
	Player() : m_timer(std::make_shared<Timer>()) {}

	Player(const std::string& name, const Color color) :
		m_name(name), m_color(color) {}

	Player(const Player& other) = default;

	Player& operator=(const Player& other) = default;

	/* Getters and setters */
	Color getColor() const { return m_color; }

	std::string getName() const { return m_name; }

	bool isTurn() const { return m_isTurn; }

	void setColor(const Color color) { m_color = color; }

	void setName(const std::string& name) { m_name = name; }

	void setTurn(const bool isTurn) { m_isTurn = isTurn; }

	/*
	* Let the player input a name.
	* @param window - the window to read from.
	* @return a string representing the name the player wants to use.
	*/
	std::string getNameFromUser(sf::RenderWindow& window) const;

	/*
	* Let the player input a move.
	* @param window - the window to read from.
	* @return a string representing the move the player wants to make.
	*/
	std::string getMoveFromUser(sf::RenderWindow& window) const;

	/*
	* handles the cases where the user wants to display some instruction or quit the game.
	* @param window - the window to read from.
	* @return a string representing the move the player wants to make.
	*/
	std::string handleInput(sf::RenderWindow& window) const;

	/*
	* Get a castle move from the player.
	* @param game - the game to get the move for.
	* @param board - the board to get the move for.
	* @param side - the side to castle on.
	* @return a castle move the player wants to make.
	*/
	std::shared_ptr<Castle> getCastle(const ChessGame& game, const std::shared_ptr<ChessBoard>& board, const Side side) const;

	/*
	* Get a promoted piece from the player.
	* @param type - the type of the piece to promote to.
	* @param color - the color of the piece to promote to.
	* @param square - the square of the piece to promote to.
	* @return a promoted piece the player wants to make.
	*/
	std::shared_ptr<ChessPiece> getPromotedPiece(const Type type, const Color color, const Square square) const;

	/*
	* Get a move from the player.
	* @param game - the game to get the move for.
	* @param window - the window to read from.
	* @return a move the player wants to make.
	*/
	std::shared_ptr<ChessMove> getMove(const ChessGame& game, sf::RenderWindow& window) const;

	/*
	* Compare two players by their color.
	* @param other - the other player to compare to.
	* @return true if the players have the same color, false otherwise.
	*/
	bool operator!=(const Player& other) const { return this->m_color != other.getColor(); }

	/*
	* Start the timer of the player.
	*/
	void startTimer() { m_timer->start(); }

	/*
	* Stop the timer of the player.
	*/
	void stopTimer() { m_timer->stop(); }

	/*
	* Get the time left for the player.
	* @return the time left for the player.
	*/
	std::chrono::duration<double> getTimeLeft() const { return TIME_LIMIT - m_timer->getDuration(); }

	/*
	* Get the time left for the player when it's his turn.
	* @return the time left for the player when it's his turn.
	*/
	std::chrono::duration<double> getDurationInTurn() const { return TIME_LIMIT - m_timer->getDurationWhenOn(); }

	/*
	* Render the time left for the player
	* @param window - the window to render to
	*/
	void renderTimeLeft(sf::RenderWindow& window) const;

	/*
	* Check if the player ran out of time.
	* @return true if the player ran out of time, false otherwise.
	*/
	bool isTimeUp() const { return m_timer->getDurationWhenOn() >= TIME_LIMIT; }

private:
	std::string m_name = "Dummy";
	Color m_color = Color::NONE;
	std::shared_ptr<Timer> m_timer;
	bool m_isTurn = false;
};