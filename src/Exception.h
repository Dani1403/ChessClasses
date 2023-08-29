#pragma once
#include <exception>

class InvalidMove : public std::exception
{
public:
	InvalidMove(std::string cause) : m_cause(cause) {};
	std::string message() const { return "Invalid move : " + m_cause; }
	const char* what() const override
	{
		return message().c_str();
	}
private:
	std::string m_cause;
};

class SquareNotValid : public std::exception
{
public:
	const char* what() const override
	{
		return "Square coordinates not valid (should be 0 <= row, col <= 7)";
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
		return "Action impossible on a piece not on board";
	}
};

class SquareNotEmpty : public std::exception
{
	const char* what() const override
	{
		return "Action impossible on a non empty square";
	}
};