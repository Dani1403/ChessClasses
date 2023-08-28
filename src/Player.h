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

	std::string getMoveFromUser(std::istream& is);

private:
	std::string m_name = "Dummy";
	Color m_color = Color::NONE;
};