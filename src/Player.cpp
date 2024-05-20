#include "ChessBoard.h"
#include "ChessGame.h"
#include "Moves/ChessMove.h"
#include "Player.h"

/*
* Let the player input a name.
* @param window - the window to read from.
* @return a string representing the name the player wants to use.
*/
std::string Player::getNameFromUser(sf::RenderWindow& window) const
{
	drawMessage(window, ASK_FOR_NAME + colorToString(m_color) + "\n");
	window.display();
	std::string name = getInput(window);
	if (name.empty())
	{
		name = "Player " + colorToString(m_color);
	}
	//check for max limit of name
	if (name.length() > 30)
	{
		name = name.substr(0, 30);
	}
	return name;
}

/*
* Let the player input a move.
* @param window - the window to read from.
* @return a string representing the move the player wants to make.
*/
std::string Player::getMoveFromUser(sf::RenderWindow& window) const
{
	drawMessage(window, ASK_FOR_MOVE);
	window.display();
	return getInput(window);
}

/*
* handles the cases where the user wants to display some instruction or quit the game.
* @param window - the window to read from.
* @return a string representing the move the player wants to make.
*/
std::string Player::handleInput(sf::RenderWindow& window) const
{
	bool isAMove = false;
	std::string input;
	do
	{
		window.display();
		input = getMoveFromUser(window);
		if (input == EXIT_SYMBOL_LOWER || input == EXIT_SYMBOL_UPPER)
			throw ExitGame();
		if (input == MOVE_ASKED_LOWER || input == MOVE_ASKED_UPPER)
		{
			drawMessage(window, MOVE_INSTRUCTION);
			continue;
		}
		if (input == CAPTURE_ASKED_LOWER || input == CAPTURE_ASKED_UPPER)
		{
			drawMessage(window, CAPTURE_INSTRUCTION);
			continue;
		}
		if (input == CASTLE_ASKED_LOWER || input == CASTLE_ASKED_UPPER)
		{
			drawMessage(window, CASTLE_INSTRUCTION);
			continue;
		}
		if (input == PROMOTION_ASKED_LOWER || input == PROMOTION_ASKED_UPPER)
		{
			drawMessage(window, PROMOTION_INSTRUCTION);
			continue;
		}
		isAMove = true;
	} while (!isAMove);
	return input;
}

/*
* Get a castle move from the player.
* @param game - the game to get the move for.
* @param board - the board to get the move for.
* @param side - the side to castle on.
* @return a castle move the player wants to make.
*/
std::shared_ptr<Castle> Player::getCastle(const ChessGame& game, const std::shared_ptr<ChessBoard>& board, const Side side) const
{
	const Square kingPos = board->getKingPosition(game.getCurrentPlayer().getColor());
	const Square rookPos = { kingPos.row,  rookColForCastle(side) };
	std::shared_ptr<King> kingToMove = std::dynamic_pointer_cast<King>(board->getPieceAt(kingPos));
	std::shared_ptr<Rook> rookToMove = std::dynamic_pointer_cast<Rook>(board->getPieceAt(rookPos));
	if (!kingToMove || !rookToMove)
		throw InvalidMove(INVALID_CASTLE_PIECES);
	return std::make_shared<Castle>(kingPos, rookToMove->getSquare(), kingToMove, rookToMove, side);

}

/*
* Get a promoted piece from the player.
* @param type - the type of the piece to promote to.
* @param color - the color of the piece to promote to.
* @param square - the square of the piece to promote to.
* @return a promoted piece the player wants to make.
*/
std::shared_ptr<ChessPiece> Player::getPromotedPiece(const Type type, const Color color, const Square square) const
{
	switch (type)
	{
	case Type::QUEEN:
		return std::make_shared<Queen>(Queen(color, square));
	case Type::ROOK:
		return std::make_shared<Rook>(Rook(color, square));
	case Type::BISHOP:
		return std::make_shared<Bishop>(Bishop(color, square));
	case Type::KNIGHT:
		return std::make_shared<Knight>(Knight(color, square));
	default:
		throw InvalidMove(INVALID_PROMOTED_PIECE);
	}
}

/*
* Get a move from the player.
* @param game - the game to get the move for.
* @param window - the window to read from.
* @return a move the player wants to make.
*/
std::shared_ptr<ChessMove> Player::getMove(const ChessGame& game, sf::RenderWindow& window) const
{
	const std::shared_ptr<ChessBoard> board = game.getChessBoard();
	const std::string input = handleInput(window);
	if (input == CASTLE_KINGSIDE || input == CASTLE_QUEENSIDE)
	{
		const Side side = input == CASTLE_KINGSIDE ? Side::KING : Side::QUEEN;
		return getCastle(game, board, side);
	}
	Square source = algebraicToSquare(input.substr(0, 2));
	Square destination = algebraicToSquare(input.substr(input.length() - 2));
	std::shared_ptr<ChessPiece> pieceToMove = board->getPieceAt(source);
	if (input.at(2) == CAPTURE_SYMBOL_UPPER ||
		input.at(2) == CAPTURE_SYMBOL_LOWER)
	{
		std::shared_ptr<ChessPiece> capturedPiece = board->getPieceAt(destination);
		return std::make_shared<Capture>(source, destination, pieceToMove, capturedPiece);
	}
	if (input[2] == PROMOTION_SYMBOL)
	{
		std::shared_ptr<Pawn> pawnToPromote = std::dynamic_pointer_cast<Pawn>(pieceToMove);
		if (!pawnToPromote)
			throw InvalidMove(INVALID_PROMOTION_PIECE);
		const Type promotionType = charToType(input[3]);
		const Color color = pawnToPromote->getColor();
		std::shared_ptr<ChessPiece> promotedPiece = getPromotedPiece(promotionType, color, { rowForPawnPromotion(color), pawnToPromote->colForPromotion() });
		return std::make_shared<Promotion>(source, promotedPiece->getSquare(), pawnToPromote, promotedPiece);
	}
	return std::make_shared<ChessMove>(source, destination, pieceToMove);
}

/*
* Render the time left for the player
* @param window - the window to render to
*/
void Player::renderTimeLeft(sf::RenderWindow& window) const
{
	sf::Font font;
	if (!font.loadFromFile("src/fonts/LEMONMILK-Regular.otf"))
		throw std::runtime_error("Could not load font");
	sf::Text text;
	text.setFont(font);
	text.setString(m_name + " has " + std::to_string((int)(getDurationInTurn().count() / 60)) + " minutes and " +
		std::to_string((int)getDurationInTurn().count() % 60) + " seconds left\n ");
	text.setCharacterSize(20);
	text.setFillColor(sf::Color::Black);
	text.setPosition(10, m_color == Color::WHITE ? 800 : 820);
	window.draw(text);
}