#pragma once

#include "../Exception.h"
#include "../utilities.h"

class ChessPiece
{
public:

	/*
	* Constructors and destructor and assignment operator
	*/

	ChessPiece(const Color& color, const Square& square, const Type& type) : m_color(color), m_position(square), m_type(type)
	{
		if (!isSquareValid(square))
			throw SquareNotValid();
	}
	ChessPiece(const ChessPiece& other) = default;
	virtual ~ChessPiece() = default;
	ChessPiece& operator=(const ChessPiece& other) = default;

	void render(sf::RenderWindow& window) const;

	/*
	* Get a string representation of the piece with color, type and position
	* @return a string representation of the piece
	*/
	std::string pieceDescription() const;

	/* Getters and Setters */

	Color getColor() const { return m_color; }
	Square getSquare() const { return m_position; }
	Type getType() const { return m_type; }

	void setPosition(const Square& newPosition) { m_position = newPosition; }
	void setType(const Type& newType) { m_type = newType; }

	/*
	* Check if two pieces are equal, i.e. have the same color, position and type
	* @param other the piece to compare with
	* @return true if the pieces are equal, false otherwise
	*/
	bool operator==(const ChessPiece& other) const { return m_color == other.m_color && m_position == other.m_position && m_type == other.m_type; }

	/*
	* Check if a Displacement is valid for the piece
	* @param source the source square
	* @param destination the destination square
	* @return true if the displacement is valid, false otherwise
	*/
	virtual bool isValidMove(const Square& source, const Square& destination) const = 0;

	/*
	* Check if a Capture is valid for the piece
	* by default, a capture is valid if the move is valid
	* @param source the source square
	* @param destination the destination square
	* @return true if the capture is valid, false otherwise
	*/
	virtual bool isValidCapture(const Square& source, const Square& destination) const { return isValidMove(source, destination); }

protected:
	Color m_color;
	Square m_position;
	Type m_type;

	std::string imageFileName() const { return typeToString(m_type) + "_" + colorToString(m_color) + (m_type == Type::KNIGHT ? "x" : ""); }
};

/*
* output stream operator for a piece
* @param os the output stream
* @param piece the piece to output
* @return the output stream
*/
std::ostream& operator<<(std::ostream& os, const ChessPiece& piece);
