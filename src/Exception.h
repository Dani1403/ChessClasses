#pragma once
#include "utilities.h"
#include <exception>

class ExitGame : public std::exception
{
public:
	const char* what() const noexcept override
	{
		return "Exiting Game";
	}
};

class TimeUp : public std::exception
{
public:
	TimeUp(std::string playerName) : m_playerName(playerName) {};
	std::string message() const { return "Time is up for " + m_playerName; }
	const char* what() const noexcept override
	{
		return message().c_str();
	}
private:
	std::string m_playerName;
};

class InvalidMove : public std::exception
{
public:
	InvalidMove(std::string cause) : m_cause(cause) {};
	std::string getCause() const { return m_cause; }
	std::string message() const { return "Invalid move : " + m_cause; }
	const char* what() const noexcept override
	{
		return message().c_str();
	}
private:
	std::string m_cause;
};

class SquareNotValid : public std::exception
{
public:
	const char* what() const noexcept override
	{
		return "Square coordinates not valid (should be 0 <= row, col <= 7)";
	}
};

class StartingSquareNotValid : public std::exception
{
public:
	const char* what() const noexcept override
	{
		return "Invalid Starting Square for Chess Piece";
	}
};

class PieceNotOnBoard : public std::exception
{
	const char* what() const noexcept override
	{
		return "Action impossible on a piece not on board";
	}
};

class SquareNotEmpty : public std::exception
{
	const char* what() const noexcept override
	{
		return "Action impossible on a non empty square";
	}
};