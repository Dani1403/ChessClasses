#include "ChessGame.h"

// INITIALIZATION

ChessGame::ChessGame() : m_chessBoard(std::make_shared<ChessBoard>(ChessBoard()))
{
	initBoard();
	m_players.push_back(Player("Daniel", Color::WHITE));
	m_players.push_back(Player("Anna", Color::BLACK));
	m_currentPlayer = m_players.front();
	std::cout << "First player : " << colorToString(m_currentPlayer.getColor()) << std::endl;
}

void ChessGame::initBoard()
{
	m_chessBoard->addInitialPieces(Color::WHITE);
	m_chessBoard->addInitialPieces(Color::BLACK);
}

// CHECK AND CHECKMATE LOGIC ~~~~~ ENDGAME LOGIC

bool ChessGame::checkPossibleCapture(std::shared_ptr<Capture> capture)
{
	try
	{
		capture->checkValidity(*this);
	}
	catch (const InvalidMove&)
	{
		return false;
	}
	return true;
}

bool ChessGame::isInCheck(const Color color)
{
	Square kingPos = m_chessBoard->getKingPosition(color);
	std::shared_ptr<ChessPiece> king = m_chessBoard->getPieceAt(kingPos);
	moveToNextPlayer();
	for (const auto& row : m_chessBoard->getBoard())
	{
		for (std::shared_ptr<ChessPiece> piece : row)
		{
			if (piece == nullptr || piece->getColor() == color)
				continue;
			const auto possibleCapture = std::make_shared<Capture>(piece->getSquare(), kingPos, piece, king);
			if (checkPossibleCapture(possibleCapture))
			{
				moveToNextPlayer();
				return true;
			}
		}
	}
	moveToNextPlayer();
	return false;
}

bool ChessGame::isInCheckmate(Color color)
{
	if (!isInCheck(color))
		return false;
	return true;
	/*
	* For each remaining piece of the color
	* Get all the available moves
	* If after the move the color is no more in check return false
	*		otherwise continue
	* return true;
	*/
}

bool ChessGame::isGameOver()
{
	/*
	* Ideally implemented with stalemate and repetitions
	*/
	return (isInCheckmate(Color::BLACK) || isInCheckmate(Color::WHITE));
}

// MOVE AND PLAYER TURN LOGIC

void ChessGame::undo()
{
	std::shared_ptr<ChessMove> move = m_moves.back();
	if (move != nullptr)
		move->undo(*this);
	m_moves.pop_back();
}

bool ChessGame::makeMove(std::shared_ptr<ChessMove> move)
{
	move->checkValidity(*this);
	move->execute(*this);
	m_moves.push_back(move);
	if (isInCheck(m_currentPlayer.getColor()))
	{
		displayMoveEndsInCheck();
		undo();
		return false;
	}
	return true;
}

void ChessGame::playerTurn()
{
	bool moved = false;
	while (!moved)
	{
		try
		{
			std::shared_ptr<ChessMove> move = m_currentPlayer.getMove(*this);
			moved = makeMove(move);
			if (!moved) continue;
		}
		catch (const InvalidMove& invalid)
		{
			std::cout << invalid.message() << std::endl << std::endl;
			continue;
		}
	}
	m_chessBoard->draw();
}

void ChessGame::moveToNextPlayer()
{
	m_players.push_back(m_players.front());
	m_players.pop_front();
	m_currentPlayer = m_players.front();
	//std::cout << "next player : " << colorToString(m_currentPlayer.getColor()) << std::endl << std::endl;
}


// MAIN LOOP 

void ChessGame::play()
{
	m_chessBoard->draw();
	while (true)
	{
		playerTurn();
		moveToNextPlayer();
	}
}