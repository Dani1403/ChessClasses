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
const char CAPTURE_SYMBOL_UPPER = 'X';
const char CAPTURE_SYMBOL_LOWER = 'x';
const char PROMOTION_SYMBOL = '=';
const char CHECK_SYMBOL = '+';
const char CHECKMATE_SYMBOL = '#';

const std::string EXIT_SYMBOL_LOWER = "q";
const std::string EXIT_SYMBOL_UPPER = "Q";
const std::string EXIT_MESSAGE = "Thank you for playing :) See you next Time !";

const std::string NOT_ON_STARTING_ROW = "The pawn you want to move twice is not on the starting row";
const std::string NOT_YOUR_COLOR = "The piece you want to move is not of your color";
const std::string YOUR_COLOR = "The piece you want to capture is of your color";
const std::string DESTINATION_SQUARE_NOT_EMPTY = "There is already a piece at the destination";
const std::string SOURCE_SQUARE_EMPTY = "There is no piece at the source";
const std::string DESTINATION_SQUARE_EMPTY = "There is no piece at the destination";
const std::string INVALID_MOVEMENT = "Invalid movement for this piece";
const std::string INVALID_CAPTURE = "Invalid capture for this piece";
const std::string OBSTACLE = "There is an obstacle";
const std::string INVALID_CASTLE_PIECES = "Invalid castle";
const std::string INVALID_CASTLE_KING = "Invalid castle for the king, it has already moved";
const std::string INVALID_CASTLE_ROOK = "Invalid castle for the rook, it has already moved";
const std::string INVALID_CASTLE_CHECK = "Invalid castle, you are in check";
const std::string INVALID_PROMOTION_PIECE = "The piece you want to promote is not a pawn";
const std::string INVALID_PROMOTED_PIECE = "You cannot promote into a pawn or a King";

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
	bool operator==(const Square& other) const
	{
		return row == other.row && col == other.col;
	}
};

bool isSquareValid(const Square& square);

Square algebraicToSquare(const std::string& notation);

std::string squareToAlgebraic(const Square& square);

std::string colorToString(const Color& color);

std::string typeToString(const Type& type);

Type charToType(const char& c);

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

int offsetForCastle(const Side side);

int rookColForCastle(const Side side);

void displayExitGameInstructions();

void displayInstructionToMove();

void displayMoveEndsInCheck();

int rowForPawnPromotion(const Color color);