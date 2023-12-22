#pragma once
#include "ChessPiece.h"

class Pawn : public ChessPiece
{
public:
	/* Constructor */
	Pawn(const Color& color, const Square& square) : ChessPiece(color, square, Type::PAWN) {}

	/* Getter and Setter for m_canPromote and m_hasMoved */

	bool canPromote() const { return m_canPromote; }
	void setCanPromote(bool promote) { m_canPromote = promote; }
	bool hasMoved() const { return m_hasMoved; }
	void setHasMoved(bool moved) { m_hasMoved = moved; }

	/*
	* @return the column of the square the pawn is on
	*/
	int colForPromotion() const { return getSquare().col; }

	/* isValidMove function
	* @param source: the square the piece is currently on
	* @param destination: the square the piece is trying to move to
	* @return: true if the move is valid, false otherwise
	* @override: the ChessPiece isValidMove function
	*/
	bool isValidMove(const Square& source, const Square& destination) const override;

	/* isValidCapture function
	* @param source: the square the piece is currently on
	* @param destination: the square the piece is trying to capture
	* @return: true if the capture is valid, false otherwise
	* @override: the ChessPiece isValidCapture function
	*/
	bool isValidCapture(const Square& source, const Square& destination) const override;

private:
	bool m_canPromote = false;
	bool m_hasMoved = false;
};