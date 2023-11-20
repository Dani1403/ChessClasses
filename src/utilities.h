#pragma once

#include <string>
#include <memory>
#include <vector>
#include <map>
#include <array>
#include <list>
#include <iostream>

const std::string CASTLE_KINGSIDE = "O-O";
const std::string CASTLE_QUEENSIDE = "O-O-O";
const char CAPTURE_SYMBOL = 'X';
const char PROMOTION_SYMBOL = '=';
const char CHECK_SYMBOL = '+';


const std::string NOT_YOUR_COLOR = "The piece you want to move is not of your color";
const std::string DESTINATION_SQUARE_NOT_EMPTY = "There is already a piece at the destination";
const std::string INVALID_MOVEMENT = "Invalid movement for this piece";
const std::string OBSTACLE = "There is an obstacle";

enum class Color { NONE = 0, WHITE, BLACK };

Color opposite(Color color);

enum class Type
{
	NONE = 0, PAWN, KNIGHT, BISHOP, QUEEN, ROOK, KING
};

enum class Side { KING, QUEEN };

struct Square
{
	int row, col;
};

bool isSquareValid(const Square& square);

Square algebraicToSquare(const std::string& notation);

std::string colorToString(const Color& color);

std::string typeToString(const Type& type);

std::string squareToAlgebraic(const Square& square);

bool isOnSameRow(const Square& s1, const Square& s2);

bool isOnSameCol(const Square& s1, const Square& s2);

bool isOnSameDiag(const Square& s1, const Square& s2);

bool isDownwardDiag(const Square& s1, const Square& s2);

bool isKnightMove(const Square& s1, const Square& s2);

int startRow(const Square& s1, const Square& s2);

int endRow(const Square& s1, const Square& s2);

int startCol(const Square& s1, const Square& s2);

int endCol(const Square& s1, const Square& s2);

int dist(const Square& s1, const Square& s2);

void displayInstructionToMove();

void displayMoveEndsInCheck();