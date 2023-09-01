#pragma once
#include "utilities.h"

class ChessMove;
class ChessBoard;

class Player
{
public:
	Player() {}
	Player(const std::string& name, Color color):
		m_name(name), m_color(color) {}

	Color getColor() const { return m_color; }

	std::string getMoveFromUser(std::istream& is) const;

	std::shared_ptr<ChessMove> getMove() const;

	bool operator!=(const Player& other) const { return this->m_color != other.getColor(); }

private:
	std::string m_name = "Dummy";
	Color m_color = Color::NONE;
};