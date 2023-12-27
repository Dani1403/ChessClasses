#include "ChessPiece.h"

/*
* Get a string representation of the piece with color, type and position
* @return a string representation of the piece
*/
std::string ChessPiece::pieceDescription() const
{
	return "Color : " + colorToString(getColor()) + "\n" +
		" Type : " + typeToString(getType()) + "\n" +
		" Square : " + squareToAlgebraic(getSquare()) + "\n";
}

void ChessPiece::render(sf::RenderWindow& window) const
{
	sf::Texture texture;
	if (!texture.loadFromFile("src/img/" + imageFileName() + ".png"))
		throw std::runtime_error("Could not load image src/img/" + imageFileName() + ".png");
	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.setPosition(getSquare().col * SQUARE_SIZE + OFFSET_X, getSquare().row * SQUARE_SIZE + OFFSET_Y);
	window.draw(sprite);
}

/*
* output stream operator for a piece
* @param os the output stream
* @param piece the piece to output
* @return the output stream
*/
std::ostream& operator<<(std::ostream& os, const ChessPiece& piece)
{
	os << "Piece: " << std::endl;
	os << piece.pieceDescription() << std::endl;
	return os;
}