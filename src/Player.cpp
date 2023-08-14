#include "Player.h"

std::string Player::getMoveFromUser(std::istream& is)
{
	std::string input;
	is >> input;
	return input;
}
