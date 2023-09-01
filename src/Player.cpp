#include "Player.h"

std::string Player::getMoveFromUser(std::istream& is) const
{
	std::string input;
	is >> input;
	return input;
}

std::shared_ptr<ChessMove> Player::getMove() const
{
	std::string input = getMoveFromUser(std::cin);

}