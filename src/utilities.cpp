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

Square getSquareFromCoords(const sf::Vector2f& coords)
{
	const int row = static_cast<int>(coords.y / SQUARE_SIZE);
	const int col = static_cast<int>(coords.x / SQUARE_SIZE);
	return Square{ row, col };
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

void drawMessage(sf::RenderWindow& window, const std::string& message)
{
	sf::Font font;
	if (!font.loadFromFile("src/fonts/LEMONMILK-Regular.otf"))
	{
		throw std::runtime_error("Font not found");
	}
	sf::Text text;
	text.setFont(font);
	text.setString(message);
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::White);
	text.setPosition(8 * SQUARE_SIZE, 8* SQUARE_SIZE);
	/* clear the part of the window where the message is drawn to avoid mess up*/
	sf::RectangleShape rect(sf::Vector2f(8 * SQUARE_SIZE, SQUARE_SIZE));
	rect.setFillColor(sf::Color::White);
	rect.setPosition(8 * SQUARE_SIZE, 8 * SQUARE_SIZE);
	window.draw(rect);
	window.draw(text);
}

void displayMessage(sf::RenderWindow& window, const std::string& message)
{
	drawMessage(window, message);
	window.display();
	sf::sleep(sf::seconds(2));
}

std::string getInput(sf::RenderWindow& window)
{
	std::string input;
	sf::Event event;
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::TextEntered)
			{
				if (event.text.unicode == '\b')
				{
					if (!input.empty())
						input.pop_back();
				}
				else if (event.text.unicode < 128)
				{
					input += static_cast<char>(event.text.unicode);
				}
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return)
			{
				return input;
			}
		}
	}
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