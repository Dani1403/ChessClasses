#pragma once

#include "../Pieces/ChessPiece.h"
#include "../utilities.h"

class ChessGame;


/*
* Card class is an abstract class that represents a card in the game
*/
class Card
{
public:
	Card() = default;
	virtual ~Card() = default;
	virtual void apply(ChessGame& game) const = 0;
	virtual void undo(ChessGame& game) const = 0;
	virtual void render(sf::RenderWindow& window) const = 0;
	virtual std::string getName() const = 0;
	virtual std::string getDescription() const = 0;
};