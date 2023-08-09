#pragma once
#include <exception>

class SquareNotValid : public std::exception
{
public:
	const char* what() const override
	{
		return "Square not Valid (should be 1 <= row, col <= 8)";
	}
};

class StartingSquareNotValid : public std::exception
{
public:
	const char* what() const override
	{
		return "Invalid Starting Square for Chess Piece";
	}
};

class PieceNotOnBoard : public std::exception
{
	const char* what() const override
	{
		return "Piece not on board";
	}
};