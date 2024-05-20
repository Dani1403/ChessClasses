#include "ChessGame.h"

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
}

/*
* Initializes a player with a name and a color
* @param player The player to initialize
* @param color The color of the player
*/
void ChessGame::initPlayer(Player& player, const Color color)
{
	player.setColor(color);
	player.setName(player.getNameFromUser(m_window));
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
* Checks if a piece is attacked on a given square, by the opposite color
* @param square The square to check
* @param color The color that is possibly attacking
*/
bool ChessGame::isSquareAttacked(const Square square, const Color color)
{
	for (const auto& row : m_chessBoard->getBoard())
	{
		for (const auto& piece : row)
		{
			if (piece == nullptr || piece->getColor() != color)
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
	const bool check = isSquareAttacked(kingPos, opposite(color));
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
* check if the game is over
* @return a string representing the issue of the game if it's over, empty string otherwise
*/
std::string ChessGame::isGameOver()
{
	std::string gameOverMessage;
	if (m_players.front().isTimeUp())
		gameOverMessage = m_players.back().getName() + " wins on time!";
	else if (m_players.back().isTimeUp())
		gameOverMessage = m_players.front().getName() + " wins on time!";
	if (!gameOverMessage.empty())
		return gameOverMessage;
	const Color currentColor = m_currentPlayer.getColor();
	if (isInCheckmate(currentColor))
		gameOverMessage = "Checkmate! " + colorToString(currentColor) + " has no legal move " + m_players.back().getName() + " wins!";
	else if (isInStaleMate(currentColor))
		gameOverMessage = "Stalemate! " + colorToString(currentColor) + " has no legal move";
	moveToNextPlayer();
	if (isInCheckmate(opposite(currentColor)))
		gameOverMessage = "Checkmate! " + colorToString(opposite(currentColor)) + " has no legal move " + m_currentPlayer.getName() + " wins!";
	else if (isInStaleMate(opposite(currentColor)))
		gameOverMessage = "Stalemate! " + colorToString(opposite(currentColor)) + " has no legal move";
	moveToNextPlayer();
	return gameOverMessage;
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
* @return an InvalidCause enum value
*/
InvalidCause ChessGame::makeMove(const std::shared_ptr<ChessMove>& move)
{
	const InvalidCause validity = move->checkValidity(*this);
	if (validity != InvalidCause::SUCCESS)
		return validity;
	move->execute(*this);
	m_moves.push_back(move);
	if (isInCheck(m_currentPlayer.getColor()))
	{
		move->undo(*this);
		return InvalidCause::MOVE_ENDS_IN_CHECK;
	}
	return InvalidCause::SUCCESS;
}

/*
* Play a turn for the current player
*	-> start the timer of the current player
*	-> get the move from the player in a separate thread
*	-> wait for the move to be ready
*	-> render the window while waiting
*	-> make the move
*	-> stop the timer of the current player
*/
void ChessGame::playerTurn()
{
	m_currentPlayer.startTimer();
	InvalidCause moved = InvalidCause::NONE;
	while (moved != InvalidCause::SUCCESS)
	{
		try
		{
			std::shared_ptr<ChessMove> move;
			std::atomic<bool> moveReady(false);
			std::atomic<bool > exitGame(false);
			std::thread getMoveThread([&]
				{
					try
					{
						move = m_currentPlayer.getMove(*this, m_window);
						moveReady = true;
					}
					catch (const ExitGame&)
					{
						exitGame = true;
					}
				});
			while (!moveReady && !exitGame)
				renderWindow();
			if (getMoveThread.joinable())
			{
				getMoveThread.join();
				if (exitGame)
					throw ExitGame();
				moved = makeMove(move);
			}
			if (moved != InvalidCause::SUCCESS)
				drawMessage(m_window, invalidCauseToString(moved) + "\n");
		}
		catch (const ExitGame&)
		{
			throw ExitGame();
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
* Render the timers to the window
*/
void ChessGame::renderTimers() const
{
	for (const auto& player : m_players)
		player.renderTimeLeft(m_window);
}

/*
* Render the game to the window
*	-> clear the window
*	-> render the board
*	-> render the timers
*	-> display the window
*/
void ChessGame::renderWindow()
{
	m_window.clear(sf::Color::White);
	m_chessBoard->render(m_window);
	renderTimers();
	m_window.display();
}

/*
* Play the game
*/
void ChessGame::play()
{
	initBoard();
	initPlayers();
	while (m_window.isOpen())
	{
		sf::Event event;
		std::string gameOverMessage = isGameOver();
		while (m_window.pollEvent(event) && gameOverMessage.empty())
		{
			if (event.type == sf::Event::Closed)
			{
				m_window.close();
				throw ExitGame();
			}
			renderWindow();
			playerTurn();
			moveToNextPlayer();
			drawMessage(m_window, "Next player's turn\n");
		}
		if (!gameOverMessage.empty())
		{
			drawMessage(m_window, gameOverMessage);
			m_window.display();
			sf::sleep(sf::seconds(5));
			throw ExitGame();
		}
	}
}