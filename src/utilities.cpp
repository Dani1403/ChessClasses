#include "utilities.h"
#include <cmath>

Color opposite(Color color)
{
	return ((color == Color::WHITE) ? Color::BLACK : Color::WHITE);
}

bool isSquareValid(const Square& square)
{
	return square.row >= 0 && square.row <= 7 && square.col >= 0 && square.col <= 7;
}

Square algebraicToSquare(const std::string& notation)
{
	int col = notation[0] - 'a';
	int row = notation[1] - '1';
	return Square{ row, col };
}

std::string squareToAlgebraic(const Square& square)
{
	char col = 'a' + square.col;
	char row = '1' + square.row;
	return std::string{ col, row };
}

bool isOnSameRow(const Square& s1, const Square& s2)
{
	return (s1.row == s2.row);
}

bool isOnSameCol(const Square& s1, const Square& s2)
{
	return (s1.col == s2.col);
}

bool isOnSameDiag(const Square& s1, const Square& s2)
{
	return (abs(s1.row - s2.row) == abs(s1.col - s2.col));
}

bool isDownwardDiag(const Square& s1, const Square& s2)
{
	return isOnSameDiag(s1, s2) && (s1.row < s2.row) && (s1.col > s2.col);
}

bool isKnightMove(const Square& s1, const Square& s2)
{
	int rowDiff = abs(s1.row - s2.row);
	int colDiff = abs(s1.col - s2.col);

	return (rowDiff == 1 && colDiff == 2) || (rowDiff == 2 && colDiff == 1);
}

int startRow(const Square& s1, const Square& s2)
{
	return std::min(s1.row, s2.row);
}

int endRow(const Square& s1, const Square& s2)
{
	return std::max(s1.row, s2.row);
}

int startCol(const Square& s1, const Square& s2)
{
	return std::min(s1.col, s2.col);
}

int endCol(const Square& s1, const Square& s2)
{
	return std::max(s1.col, s2.col);
}

int dist(const Square& s1, const Square& s2)
{
	int rowDiff = s1.row - s2.row;
	int colDiff = s1.col - s2.col;
	return static_cast<int>(sqrt(rowDiff*rowDiff + colDiff*colDiff));
}

void askForBlackPlayerName(std::string& name)
{
  std::cout << "Please enter the name of the black player : ";
}

void displayWelcomeMessage()
{
  std::cout << "Welcome to Chess++" << std::endl;
}

void askForWhitePlayerName(std::string& name)
{
  std::cout << "Please enter the name of the white player : ";
}

void displayExitGameInstructions()
{
	std::cout << "  - To exit the game please enter 'quit'" << std::endl;
}

void askForName(const Color color)
{
  std::cout << "Please enter your name for " + colorToString(color) + " ";
}

void getCastleInstruction()
{
  std::cout << " - To get the instructions for castling please enter 'castling'" << std::endl;
}

void getPromotionInstruction()
{
  std::cout << " - To get the instructions for pawn promotion please enter 'promotion'" << std::endl;
}

void getMoveInstruction()
{
  std::cout << " - To get the instructions for moving a piece please enter 'move'" << std::endl;
}

void getCaptureInstruction()
{
  std::cout << " - To get the instructions for capturing a piece please enter 'capture'" << std::endl;
}


void askForMove()
{
    std::cout << "Please enter your move : ";
}


void displayMoveInstruction()
{
	std::cout << "To enter your move, follow the instruction below: " << std::endl;
	std::cout << "1 - Enter the case of the piece you want to move " << std::endl;
	std::cout << "2 - Enter the destination case for your piece" << std::endl;
	std::cout << "Example : e2e4" << std::endl;
}

void displayCaptureInstruction()
{
	std::cout << "To enter your capture, follow the instruction below: " << std::endl;
	std::cout << "1 - Enter the case of the piece you want to move " << std::endl;
	std::cout << "2 - Enter X" << std::endl;
	std::cout << "3 - Enter the destination case for your piece" << std::endl;
	std::cout << "Example : e4Xd5" << std::endl;
}

void displayCastleInstruction()
{
	std::cout << "  - Enter O-O to Castle King side and O-O-O for QueenSide" << std::endl;
}

void displayPromotionInstruction()
{
	std::cout << " To Promote a Pawn: " << std::endl;
	std::cout << "1 - Enter the case where the pawn is (example : d7)" << std::endl;
	std::cout << "2 - Enter symbol = " << std::endl;
	std::cout << "3 - Enter the type of the promoted Piece (Q - Queen, k - Knight, B - Bishop, R - Rook)" << std::endl;
}


void displayInstructions()
{
	displayExitGameInstructions();
	getMoveInstruction();
  getCaptureInstruction();
  getCastleInstruction();
  getPromotionInstruction();
}


void displayMoveEndsInCheck()
{
	std::cout << "The move you want to play result in you being in check" << std::endl << std::endl;
}

std::string colorToString(const Color& color)
{
	return color == Color::WHITE ? "white" : "black";
}

std::string typeToString(const Type& type)
{
	switch (type) 
	{
	case Type::KING:
		return "K";
	case Type::ROOK:
		return "R";
	case Type::QUEEN:
		return "Q";
	case Type::KNIGHT:
		return "k";
	case Type::PAWN:
		return "P";
	case Type::BISHOP:
		return "B";
	default:
		return "None";
	}
}

Type charToType(const char& c)
{
		switch (c)
	{
	case 'K':
		return Type::KING;
	case 'R':
		return Type::ROOK;
	case 'Q':
		return Type::QUEEN;
	case 'k':
		return Type::KNIGHT;
	case 'P':
		return Type::PAWN;
	case 'B':
		return Type::BISHOP;
	default:
		return Type::NONE;
	}
}

int offsetForCastle(const Side side)
{
	return side == Side::KING ? 2 : -2;
}

int rookColForCastle(const Side side)
{
	return side == Side::KING ? 7 : 0;
}

int rowForPawnPromotion(const Color color)
{
	return color == Color::WHITE ? 7 : 0;
}