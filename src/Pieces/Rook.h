#pragma once
#include "ChessPiece.h"

class Rook : public ChessPiece
{
public:
	/* Constructor */
	Rook(const Color& color, const Square& square) : ChessPiece(color, square, Type::ROOK) {}

	/* Getter and Setter for m_hasMoved */
	bool hasMoved() const { return m_hasMoved; }
	void setHasMoved(bool moved) { m_hasMoved = moved; }

	/* isValidMove function
	* @param source: the square the piece is currently on
	* @param destination: the square the piece is trying to move to
	* @return: true if the move is valid, false otherwise
	* @override: the ChessPiece isValidMove function
	*/
	bool isValidMove(const Square& source, const Square& destination) const override;

	/*
	* The isValidCapture function is not needed for this class
	* because the default implementation in ChessPiece is sufficient
	*/

private:
	bool m_hasMoved = false;
};