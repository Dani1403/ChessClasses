#pragma once
#include <cmath>
#include <string>
#include <memory>
#include <vector>
#include <map>
#include <array>
#include <list>
#include <iostream>
#include <chrono>

const std::chrono::duration<double> TIME_LIMIT = std::chrono::seconds(15 * 60);


const std::string CASTLE_KINGSIDE = "O-O";
const std::string CASTLE_QUEENSIDE = "O-O-O";
const char CAPTURE_SYMBOL_UPPER = 'X';
const char CAPTURE_SYMBOL_LOWER = 'x';
const char PROMOTION_SYMBOL = '=';
const char CHECK_SYMBOL = '+';
const char CHECKMATE_SYMBOL = '#';

const std::string EXIT_SYMBOL_LOWER = "quit";
const std::string EXIT_SYMBOL_UPPER = "Quit";
const std::string EXIT_MESSAGE = "Thank you for playing :) See you next Time !";

const std::string MOVE_ASKED_LOWER = "move";
const std::string MOVE_ASKED_UPPER = "Move";
const std::string CAPTURE_ASKED_LOWER = "capture";
const std::string CAPTURE_ASKED_UPPER = "Capture";
const std::string PROMOTION_ASKED_LOWER = "promote";
const std::string PROMOTION_ASKED_UPPER = "Promote";
const std::string CASTLE_ASKED_LOWER = "castle";
const std::string CASTLE_ASKED_UPPER = "Castle";

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
const std::string NO_LAST_MOVE = "You cannot EnPassant in the first move";
const std::string NOT_PAWN = "The piece you want to move is not a pawn";
const std::string NOT_EN_PASSANT_ROW = "The EnPassant pawn is not on a valid row";
const std::string NOT_EN_PASSANT_COL = "The EnPassant pawn is not on a valid column";
const std::string LAST_MOVE_NOT_PAWN = "The last move was not a pawn move";
const std::string INVALID_LAST_MOVE = "The last move was not a double pawn move";

enum class Color { NONE = 0, WHITE, BLACK };

Color opposite(const Color color);

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

void askForWhitePlayerName(std::string& name);

void askForBlackPlayerName(std::string& name);

void displayWelcomeMessage();

void displayExitGameInstructions();

void askForName(const Color color);

void askForMove();

void displayInstructions();

void getCastleInstruction();

void getMoveInstruction();

void getCaptureInstruction();

void getPromotionInstruction();

void displayMoveInstruction();

void displayCaptureInstruction();

void displayPromotionInstruction();

void displayCastleInstruction();

void displayMoveEndsInCheck();

int rowForPawnPromotion(const Color color);

bool isValidColumnForEnPassant(int col1, int col2) {return abs(col1 - col2) == 1 };