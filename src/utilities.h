#pragma once

#include <array>
#include <atomic>
#include <chrono>
#include <cmath>
#include <condition_variable>
#include <functional>
#include <future>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <mutex>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>
#include <thread>
#include <vector>


const int WINDOW_WIDTH = 2000;
const int WINDOW_HEIGHT = 2000;
const std::chrono::duration<double> TIME_LIMIT = std::chrono::seconds(15 * 60);
const float SQUARE_SIZE = 90.0f;
const int ICON_SIZE = 60;
const int SQUARE_OUTLINE_THICKNESS = 2;
#define BLACK_SQUARE_COLOR (sf::Color(87, 58, 46))
#define WHITE_SQUARE_COLOR (sf::Color(138, 120, 93))

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

const std::string NOT_ON_STARTING_ROW = "The pawn you want to move twice is not on the starting row\n";
const std::string NOT_YOUR_COLOR = "The piece you want to move is not of your color\n";
const std::string YOUR_COLOR = "The piece you want to capture is of your color\n";
const std::string DESTINATION_SQUARE_NOT_EMPTY = "There is already a piece at the destination\n";
const std::string SOURCE_SQUARE_EMPTY = "There is no piece at the source\n";
const std::string DESTINATION_SQUARE_EMPTY = "There is no piece at the destination\n";
const std::string INVALID_MOVEMENT = "Invalid movement for this piece\n";
const std::string INVALID_CAPTURE = "Invalid capture for this piece\n";
const std::string OBSTACLE = "There is an obstacle\n";
const std::string INVALID_CASTLE_PIECES = "Invalid castle\n";
const std::string INVALID_CASTLE_KING = "Invalid castle for the king, it has already moved\n";
const std::string INVALID_CASTLE_ROOK = "Invalid castle for the rook, it has already moved\n";
const std::string INVALID_CASTLE_CHECK = "Invalid castle, you are in check\n";
const std::string INVALID_PROMOTION_PIECE = "The piece you want to promote is not a pawn\n";
const std::string INVALID_PROMOTED_PIECE = "You cannot promote into a pawn or a King\n";
const std::string MOVE_ENDS_IN_CHECK = "This move ends in you being in check\n";


const std::string WELCOME_MESSAGE = "Welcome to Chess !\n";
const std::string EXIT_GAME_MESSAGE = "To exit the game, type 'quit'\n";
const std::string ASK_FOR_NAME = "Please enter your name for ";
const std::string ASK_FOR_MOVE = "Please enter your move: \n";

const std::string GET_CASTLE_INSTRUCTION = "To get a castle instruction, type 'castling'\n";
const std::string CASTLE_INSTRUCTION = "To castle, follow the instruction below: \n" \
								"1 - Enter O-O to Castle King side and O-O-O for QueenSide \n";
const std::string GET_MOVE_INSTRUCTION = "To get the move instruction, type 'move'\n";
const std::string MOVE_INSTRUCTION = "To enter your move, follow the instruction below: \n " \
								"1 - Enter the square of the piece you want to move \n" \
								"2 - Enter the destination case for your piece \n" \
								"Example : e2e4 \n";
const std::string GET_CAPTURE_INSTRUCTION = "To get the capture instruction, type 'capture'\n";
const std::string CAPTURE_INSTRUCTION = "To enter your capture, follow the instruction below: \n" \
									"1 - Enter the square of the piece you want to move \n" \
									"2 - Enter X \n" \
									"3 - Enter the destination case for your piece \n" \
									"Example : e4Xd5 \n";
const std::string GET_PROMOTION_INSTRUCTION = "To get the promotion instruction, type 'promote'\n";
const std::string PROMOTION_INSTRUCTION = "To Promote a Pawn: \n" \
									"1 - Enter the square where the pawn is currently (example : d7) \n" \
									"2 - Enter symbol = \n" \
									"3 - Enter the type of the promoted Piece (q - Queen, n - Knight, b - Bishop, r - Rook) \n";

const std::string MOVE_ENDS_IN_CHECK_MESSAGE = "This move ends in you being in check\n";


void drawMessage(sf::RenderWindow& window, const std::string& message);

std::string getInput(sf::RenderWindow& window);


enum class InvalidCause
{
	NONE = 0, NOT_ON_STARTING_ROW, NOT_YOUR_COLOR, YOUR_COLOR, DESTINATION_SQUARE_NOT_EMPTY, SOURCE_SQUARE_EMPTY,
	DESTINATION_SQUARE_EMPTY, INVALID_MOVEMENT, INVALID_CAPTURE, OBSTACLE, INVALID_CASTLE_PIECES, INVALID_CASTLE_KING,
	INVALID_CASTLE_ROOK, INVALID_CASTLE_CHECK, INVALID_PROMOTION_PIECE, INVALID_PROMOTED_PIECE, MOVE_ENDS_IN_CHECK, SUCCESS
};

std::string invalidCauseToString(const InvalidCause cause);

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

Square getSquareFromCoords(const sf::Vector2f& coords);

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

int rowForPawnPromotion(const Color color);

