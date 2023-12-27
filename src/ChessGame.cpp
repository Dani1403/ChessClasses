#include "ChessGame.h"

/*
 * Constructor
 */
ChessGame::ChessGame() : m_chessBoard(std::make_shared<ChessBoard>(ChessBoard()))
{
}

/*
* Initializes the players with their names and colors
*/
void ChessGame::initPlayers()
{
	const auto player1 = std::make_unique<Player>();
	const auto player2 = std::make_unique<Player>();
	initPlayer(*player1, Color::WHITE);
	initPlayer(*player2, Color::BLACK);
	m_players.push_back(*player1);
	m_players.push_back(*player2);
	m_currentPlayer = m_players.front();
	std::cout << "First player : " << m_currentPlayer.getName() << std::endl << std::endl;
}

/*
* Initializes a player with a name and a color
*/
void ChessGame::initPlayer(Player& player, const Color color)
{
	player.setColor(color);
	player.setName(player.getNameFromUser(std::cin, color));
}

/*
* Initializes the board with the pieces in their starting positions
*/
void ChessGame::initBoard()
{
	m_chessBoard->addInitialPieces(Color::WHITE);
	m_chessBoard->addInitialPieces(Color::BLACK);
}

/*
* Checks if a piece is attacked on a given square
* @param square The square to check
* @param color The color of the piece to check
*/
bool ChessGame::isSquareAttacked(const Square square, const Color color)
{
	for (const auto& row : m_chessBoard->getBoard())
	{
		for (const auto& piece : row)
		{
			if (piece == nullptr || piece->getColor() == color)
				continue;
			const auto possibleCapture = std::make_shared<Capture>(piece->getSquare(), square, piece, m_chessBoard->getPieceAt(square));
			if (possibleCapture->checkPossibleMove(*this))
				return true;
		}
	}
	return false;
}

/*
* check if a given color is in check
* @param color The color to check
* @return True if the color is in check, false otherwise
*/
bool ChessGame::isInCheck(const Color color)
{
	const Square kingPos = m_chessBoard->getKingPosition(color);
	moveToNextPlayer();
	const bool check = isSquareAttacked(kingPos, color);
	moveToNextPlayer();
	return check;
}

/*
* Checks if a given move can be made using its checkPossibleMove function
* @param move The move to check
* @param possibleMoves a vector of possible moves
* if the move is valid, append it to the vector of possible moves
*/
void ChessGame::appendMove(std::vector<std::shared_ptr <ChessMove>>& moves, std::shared_ptr<ChessMove> move)
{
	if (move->checkPossibleMove(*this))
		moves.push_back(move);
}

/*
* Creates a regular move from an existing piece and a destination square
* @param moves a vector of possible moves
* @param piece The piece to move
* @param destSquare The destination square
* if the move is valid, append it to the vector of possible moves
*/
void ChessGame::appendRegular(std::vector<std::shared_ptr <ChessMove>>& moves, std::shared_ptr<ChessPiece> piece, Square destSquare)
{
	const std::shared_ptr<ChessMove> regularMove = std::make_shared<ChessMove>(piece->getSquare(), destSquare, piece);
	appendMove(moves, regularMove);
}

/*
* Creates a capture move from an existing piece, a captured piece and a destination square
* @param moves a vector of possible moves
* @param piece The piece to move
* @param captured The piece to capture
* @param destSquare The destination square
* if the capture is valid, append it to the vector of possible moves
*/
void ChessGame::appendCapture(std::vector<std::shared_ptr <ChessMove>>& moves, std::shared_ptr<ChessPiece> piece, std::shared_ptr<ChessPiece> captured, Square destSquare)
{
	const std::shared_ptr<ChessMove> capture = std::make_shared<Capture>(piece->getSquare(), destSquare, piece, captured);
	appendMove(moves, capture);
}

/*
* Creates a promotion move from an existing pawn and a destination square
* @param moves a vector of possible moves
* @param pawn The pawn to move
* @param destSquare The destination square
* if the promotion is valid, append it to the vector of possible moves
*/
void ChessGame::appendPromotion(std::vector<std::shared_ptr<ChessMove>>& moves, std::shared_ptr<Pawn> pawn, Square destSquare)
{
	const Color color = pawn->getColor();
	const std::shared_ptr<ChessMove> promotion = std::make_shared<Promotion>(pawn->getSquare(), destSquare, pawn, getCurrentPlayer().getPromotedPiece(Type::QUEEN, color, { rowForPawnPromotion(color), pawn->colForPromotion() }));
	appendMove(moves, promotion);
}

/*
* Create two castle moves from an existing king
* @param moves a vector of possible moves
* if the castle is valid, append it to the vector of possible moves
*/
void ChessGame::appendCastle(std::vector<std::shared_ptr<ChessMove>>& moves)
{
	const std::shared_ptr<ChessMove> castleKing = getCurrentPlayer().getCastle(*this, m_chessBoard, Side::KING);
	appendMove(moves, castleKing);
	const std::shared_ptr<ChessMove> castleQueen = getCurrentPlayer().getCastle(*this, m_chessBoard, Side::QUEEN);
	appendMove(moves, castleQueen);
}

/*
*  Get all the possible moves for a given piece
* @param piece The piece to get the moves for
* @return A vector containing all the possible moves for the piece
*/
std::vector<std::shared_ptr<ChessMove>> ChessGame::getPossibleMovesForPiece(std::shared_ptr<ChessPiece> pieceToCheck)
{
	std::vector<std::shared_ptr<ChessMove>> possibleMoves;
	for (int row = 0; row < m_chessBoard->BOARD_SIZE; row++)
	{
		for (int col = 0; col < m_chessBoard->BOARD_SIZE; col++)
		{
			std::shared_ptr<ChessPiece> pieceToCapture = m_chessBoard->getPieceAt({ row, col });
			if (pieceToCapture)
				appendCapture(possibleMoves, pieceToCheck, pieceToCapture, { row, col });
			appendRegular(possibleMoves, pieceToCheck, { row, col });
			std::shared_ptr<King> king = std::dynamic_pointer_cast<King>(pieceToCheck);
			if (king)
				appendCastle(possibleMoves);
			std::shared_ptr<Pawn> pawn = std::dynamic_pointer_cast<Pawn>(pieceToCheck);
			if (pawn)
				appendPromotion(possibleMoves, pawn, { row, col });
		}
	}
	return possibleMoves;
}

/*
* for all possible moves, check if the king is still in check after the move
* @param possibleMoves The possible moves to check
* @param color The color to check
* @return true if the king is not in check after at least one move, false otherwise
*/
bool ChessGame::checkPossibleMoves(const std::vector<std::shared_ptr<ChessMove>>& possibleMoves, Color color)
{
	for (const auto& move : possibleMoves)
	{
		move->execute(*this);
		if (!isInCheck(color))
		{
			move->undo(*this);
			return true;
		}
		move->undo(*this);
	}
	return false;
}

/*
* check if a given color has a valid move
* @param color The color to check
* @return True if the color has a valid move, false otherwise
*/
bool ChessGame::colorHasValidMove(const Color color)
{
	for (int row = 0; row < m_chessBoard->BOARD_SIZE; row++)
	{
		for (int col = 0; col < m_chessBoard->BOARD_SIZE; col++)
		{
			std::shared_ptr<ChessPiece> piece = m_chessBoard->getPieceAt({ row, col });
			if (piece == nullptr || piece->getColor() != color)
				continue;
			std::vector<std::shared_ptr<ChessMove>> possibleMoves = getPossibleMovesForPiece(piece);
			const bool hasValidMove = checkPossibleMoves(possibleMoves, color);
			if (hasValidMove)
				return true;
		}
	}
	return false;
}

/*
* check if a given color is in checkmate
* @param color The color to check
* @return True if the color is in checkmate, false otherwise
*/
bool ChessGame::isInCheckmate(const Color color)
{
	if (!isInCheck(color))
		return false;
	return !colorHasValidMove(color);
}

/*
* check if a given color is in stalemate
* @param color The color to check
* @return True if the color is in stalemate, false otherwise
*/
bool ChessGame::isInStaleMate(const Color color)
{
	if (isInCheck(color))
		return false;
	return !colorHasValidMove(color);
}

/*
* Handle the case where a player's time is up
* @param player The player to check if his time is up
* if the time is up, display defeat message and exit the game
*/
void ChessGame::handleTimeUp(const Player& player) const
{
	if (player.isTimeUp())
	{
		std::cout << player.getName() << " ran out of time!" << std::endl;
		player.displayDefeat();
		throw ExitGame();
	}
}

/*
* check if the game is over
* @return True if the game is over, false otherwise
*/
bool ChessGame::isGameOver()
{
	handleTimeUp(m_currentPlayer);
	handleTimeUp(m_players.back());
	const Color currentColor = m_currentPlayer.getColor();
	if (isInCheckmate(currentColor))
	{
		m_players.back().displayVictory();
		return true;
	}
	else if (isInStaleMate(currentColor))
	{
		std::cout << "Stalemate! " + colorToString(currentColor) + " has no legal move " << std::endl;
		return true;
	}
	moveToNextPlayer();
	if (isInCheckmate(opposite(currentColor)))
	{
		m_players.back().displayVictory();
		return true;
	}
	else if (isInStaleMate(opposite(currentColor)))
	{
		std::cout << "Stalemate! " + colorToString(opposite(currentColor)) + " has no legal move" << std::endl;
		return true;
	}
	moveToNextPlayer();
	return false;
}

/*
* Undoes the last move
*/
void ChessGame::undo()
{
	if (m_moves.empty())
		return;
	const std::shared_ptr<ChessMove> move = m_moves.back();
	if (move != nullptr)
		move->undo(*this);
	m_moves.pop_back();
}

/*
* Checks if the move is valid and if it is, makes the move
* @param move The move to be made
* @return True if the move was made, false otherwise
*/
bool ChessGame::makeMove(const std::shared_ptr<ChessMove>& move)
{
	move->checkValidity(*this);
	move->execute(*this);
	m_moves.push_back(move);
	if (isInCheck(m_currentPlayer.getColor()))
	{
		displayMoveEndsInCheck();
		move->undo(*this);
		return false;
	}
	return true;
}

/*
* Play a turn for the current player
*/
void ChessGame::playerTurn()
{
	m_currentPlayer.startTimer();
	bool moved = false;
	while (!moved)
	{
		try
		{
			std::shared_ptr<ChessMove> move = m_currentPlayer.getMove(*this);
			moved = makeMove(move);
		}
		catch (const InvalidMove& invalid)
		{
			std::cout << invalid.message() << std::endl << std::endl;
		}
	}
	m_currentPlayer.stopTimer();
}

/*
* moves the game to the next player
*/
void ChessGame::moveToNextPlayer()
{
	m_players.push_back(m_players.front());
	m_players.pop_front();
	m_currentPlayer = m_players.front();
}

/*
* display the next player to play on the console
*/
void ChessGame::displayNextPlayer() const
{
	std::cout << "Next player : " << m_currentPlayer.getName() << std::endl << std::endl;
}

/*
* Play the game
*	@param window - the window to render to
*/
void ChessGame::play(sf::RenderWindow& window)
{
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		displayWelcomeMessage();
		initBoard();
		window.clear(sf::Color::White);
		m_chessBoard->render(window);
		window.display();
		initPlayers();
		while (!isGameOver())
		{
			window.clear(sf::Color::White);
			m_chessBoard->render(window);
			window.display();
			window.setActive(true);
			for (const auto& player : m_players)
				player.displayTimeLeft();
			playerTurn();
			moveToNextPlayer();
			displayNextPlayer();
		}
	}
}