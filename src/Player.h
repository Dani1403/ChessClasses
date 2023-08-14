#pragma once
#include "utilities.h"

class ChessMove;
class ChessBoard;

class Player
{
public:
	Player(const std::string& name, Color color):
		m_name(name), m_color(color) {}

	Color getColor() const { return m_color; }

	ChessMove* getMoveFromCommandLine(const std::ostream& os);

private:
	std::string m_name;
	Color m_color;
};