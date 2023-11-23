#include "utilities.h"

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

void displayExitGameInstructions()
{
	std::cout << "  - To exit the game please enter the letter q" << std::endl;
}

void displayInstructionToMove()
{
	std::cout << "To enter your move, follow the instruction below: " << std::endl;
	std::cout << "1 - Enter the case of the piece you want to move " << std::endl;
	std::cout << "2 - Enter X if you want to capture" << std::endl;
	std::cout << "3 - Enter the destination case for your piece" << std::endl;
	std::cout << "Example : e2e4 or e4Xd5" << std::endl;
	displayInstructionToCastle();
	displayInstructionToPromote();
	std::cout << "Enter your move : ";
}

void displayInstructionToCastle()
{
	std::cout << "  - Enter O-O to Castle King side and O-O-O for QueenSide" << std::endl;
}

void displayInstructionToPromote()
{
	std::cout << " To Promote a Pawn: " << std::endl;
	std::cout << "1 - Enter the case where the pawn is (example : d7)" << std::endl;
	std::cout << "2 - Enter symbol = " << std::endl;
	std::cout << "3 - Enter the type of the promoted Piece (Q - Queen, k - Knight, B - Bishop, R - Rook)" << std::endl;
}


void displayMoveEndsInCheck()
{
	std::cout << "The move you want to play result in you being in check" << std::endl;
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