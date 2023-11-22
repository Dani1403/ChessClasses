#pragma once

#include "../utilities.h"
#include "../Exception.h"

class ChessPiece
{
public:
	ChessPiece(const Color& color, const Square& square, const Type& type) : m_color(color), m_position(square), m_type(type) 
	{
		if (!isSquareValid(square))
			throw SquareNotValid();
	}
	ChessPiece(const ChessPiece& other) = default;
	virtual ~ChessPiece() = default;
	ChessPiece& operator=(const ChessPiece& other) = default;

	std::string pieceDescription() const;

	Color getColor() const { return m_color; }
	Square getSquare() const { return m_position; }
	Type getType() const { return m_type; }

	bool operator==(const ChessPiece& other) const { return m_color == other.m_color && m_position == other.m_position && m_type == other.m_type; }

	void setPosition(const Square& newPosition) { m_position = newPosition; }
	void setType(const Type& newType) { m_type = newType; }

	virtual bool isValidMove(const Square& source, const Square& destination) const = 0;
	virtual bool isValidCapture(const Square& source, const Square& destination) const { return isValidMove(source, destination); }

protected:
	Color m_color;
	Square m_position;
	Type m_type;
};

std::ostream& operator<<(std::ostream& os, const ChessPiece& piece);
