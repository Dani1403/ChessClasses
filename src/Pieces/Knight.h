#pragma once
#include "ChessPiece.h"

class Knight : public ChessPiece
{
public:
	/*Constructor*/
	Knight(const Color& color, const Square& square) : ChessPiece(color, square, Type::KNIGHT) {}

	/*
	* isValidMove function using the Knight's movement rules declared in utilities.h
	* @param source: the square the piece is currently on
	* @param destination: the square the piece is trying to move to
	* @return: true if the move is valid, false otherwise
	* @override: the ChessPiece isValidMove function
	*/
	bool isValidMove(const Square& source, const Square& destination) const override;
};