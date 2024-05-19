#include "utilities.h"

std::string invalidCauseToString(const InvalidCause cause)
{
	switch (cause)
	{
	case InvalidCause::NONE:
		return "NONE";
	case InvalidCause::SUCCESS:
		return "SUCCESS";
	case InvalidCause::NOT_ON_STARTING_ROW:
		return NOT_ON_STARTING_ROW;
	case InvalidCause::NOT_YOUR_COLOR:
		return NOT_YOUR_COLOR;
	case InvalidCause::YOUR_COLOR:
		return YOUR_COLOR;
	case InvalidCause::DESTINATION_SQUARE_NOT_EMPTY:
		return DESTINATION_SQUARE_NOT_EMPTY;
	case InvalidCause::SOURCE_SQUARE_EMPTY:
		return SOURCE_SQUARE_EMPTY;
	case InvalidCause::DESTINATION_SQUARE_EMPTY:
		return DESTINATION_SQUARE_EMPTY;
	case InvalidCause::INVALID_MOVEMENT:
		return INVALID_MOVEMENT;
	case InvalidCause::INVALID_CAPTURE:
		return INVALID_CAPTURE;
	case InvalidCause::OBSTACLE:
		return OBSTACLE;
	case InvalidCause::INVALID_CASTLE_PIECES:
		return INVALID_CASTLE_PIECES;
	case InvalidCause::INVALID_CASTLE_KING:
		return INVALID_CASTLE_KING;
	case InvalidCause::INVALID_CASTLE_ROOK:
		return INVALID_CASTLE_ROOK;
	case InvalidCause::INVALID_CASTLE_CHECK:
		return INVALID_CASTLE_CHECK;
	case InvalidCause::INVALID_PROMOTION_PIECE:
		return INVALID_PROMOTION_PIECE;
	case InvalidCause::INVALID_PROMOTED_PIECE:
		return INVALID_PROMOTED_PIECE;
	case InvalidCause::MOVE_ENDS_IN_CHECK:
		return MOVE_ENDS_IN_CHECK;
	}
}

Color opposite(const Color color)
{
	return ((color == Color::WHITE) ? Color::BLACK : Color::WHITE);
}

bool isSquareValid(const Square& square)
{
	return square.row >= 0 && square.row <= 7 && square.col >= 0 && square.col <= 7;
}

Square algebraicToSquare(const std::string& notation)
{
	const int col = notation[0] - 'a';
	const int row = notation[1] - '1';
	return Square{ row, col };
}

std::string squareToAlgebraic(const Square& square)
{
	const char col = 'a' + square.col;
	const char row = '1' + square.row;
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
	const int rowDiff = abs(s1.row - s2.row);
	const int colDiff = abs(s1.col - s2.col);

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
	const int rowDiff = s1.row - s2.row;
	const int colDiff = s1.col - s2.col;
	return static_cast<int>(sqrt(rowDiff * rowDiff + colDiff * colDiff));
}

void displayWelcomeMessage()
{
	std::cout << "Welcome to Chess++" << std::endl;
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
	std::cout << "1 - Enter the square of the piece you want to move " << std::endl;
	std::cout << "2 - Enter the destination case for your piece" << std::endl;
	std::cout << "Example : e2e4" << std::endl;
}

void displayCaptureInstruction()
{
	std::cout << "To enter your capture, follow the instruction below: " << std::endl;
	std::cout << "1 - Enter the square of the piece you want to move " << std::endl;
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
	std::cout << "1 - Enter the square where the pawn is currently (example : d7)" << std::endl;
	std::cout << "2 - Enter symbol = " << std::endl;
	std::cout << "3 - Enter the type of the promoted Piece (q - Queen, n - Knight, b - Bishop, r - Rook)" << std::endl;
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
	std::cout << MOVE_ENDS_IN_CHECK << std::endl << std::endl;
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
		return "k";
	case Type::ROOK:
		return "r";
	case Type::QUEEN:
		return "q";
	case Type::KNIGHT:
		return "n";
	case Type::PAWN:
		return "p";
	case Type::BISHOP:
		return "b";
	default:
		return "None";
	}
}

Type charToType(const char& c)
{
	switch (c)
	{
	case 'k':
		return Type::KING;
	case 'r':
		return Type::ROOK;
	case 'q':
		return Type::QUEEN;
	case 'n':
		return Type::KNIGHT;
	case 'p':
		return Type::PAWN;
	case 'b':
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