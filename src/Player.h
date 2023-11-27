#pragma once
#include "utilities.h"
#include "Moves/Castle.h"
#include "Moves/Promotion.h"
#include "Moves/Capture.h"



class ChessMove;
class ChessBoard;
class ChessGame;

class Player
{
public:
	Player() = default;
	Player(const std::string& name, const Color color):
		m_name(name), m_color(color) {}

	Color getColor() const { return m_color; }

	/*
	 * Let the player input a move.
	 * @param is - the input stream to read from.
	 * @return a string representing the move the player wants to make.
	 */
	std::string getMoveFromUser(std::istream& is) const;

	/*
	 * Get a castle move from the player.
	 * @param game - the game to get the move for.
	 * @param board - the board to get the move for.
	 * @param side - the side to castle on.
	 * @return a castle move the player wants to make.
	 */
	std::shared_ptr<Castle> getCastle(const ChessGame& game, std::shared_ptr<ChessBoard> board, const Side side) const;

	/*
	 * Get a promoted piece from the player.
	 * @param type - the type of the piece to promote to.
	 * @param color - the color of the piece to promote to.
	 * @param square - the square of the piece to promote to.
	 * @return a promoted piece the player wants to make.
	 */
	std::shared_ptr<ChessPiece> getPromotedPiece(Type type, Color color, Square square) const;

	/*
	 * Get a move from the player.
	 * @param game - the game to get the move for.
	 * @return a move the player wants to make.
	 */
	std::shared_ptr<ChessMove> getMove(const ChessGame& game) const;

	/*
	 * Compare two players by their color.
	 * @param other - the other player to compare to.
	 * @return true if the players have the same color, false otherwise.
	 */
	bool operator!=(const Player& other) const { return this->m_color != other.getColor(); }

	void displayVictory() const { std::cout << m_name << " won the game!" << std::endl; }

	void displayDraw() const { std::cout << "The game ended in a draw!" << std::endl; }

	void displayDefeat() const { std::cout << m_name << " lost the game!" << std::endl; }

private:
	std::string m_name = "Dummy";
	Color m_color = Color::NONE;

};