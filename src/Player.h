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

private:
	std::string m_name = "Dummy";
	Color m_color = Color::NONE;

	std::shared_ptr<Castle> getCastle(const ChessGame& game, std::shared_ptr<ChessBoard> board, const Side side) const;
	std::shared_ptr<ChessPiece> getPromotedPiece(Type type, Color color, Square square) const;
};