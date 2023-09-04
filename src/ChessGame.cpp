#include "ChessGame.h"

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

void ChessGame::moveToNextPlayer()
{
	m_players.push_back(m_players.front());
	m_players.pop_front();
	m_currentPlayer = m_players.front();
	std::cout << "next player : " << colorToString(m_currentPlayer.getColor()) << std::endl << std::endl;
}

void ChessGame::play()
{
	m_chessBoard->draw();
	while (!isGameOver())
	{
		playerTurn();
		moveToNextPlayer();
	}
}

bool ChessGame::makeMove(std::shared_ptr<ChessMove> move)
{
	move->checkValidity(*this);
	move->execute(*this);
	if (isInCheck(m_currentPlayer.getColor()))
	{
		move->undo(*this);
		m_moves.pop_back();
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
		}
		catch (const InvalidMove& invalid)
		{
			std::cout << invalid.message() << std::endl << std::endl;
			continue;
		}
	}
	m_chessBoard->draw();
}

void ChessGame::undo()
{
	std::shared_ptr<ChessMove> move = m_moves.back();
	if (move != nullptr)
		move->undo(*this);
	m_moves.pop_back();
}

bool ChessGame::isInCheck(Color color)
{
	Square kingPos = m_chessBoard->getKingPosition(color);
	std::shared_ptr<ChessPiece> king = m_chessBoard->getPieceAt(kingPos);
	for (const auto& row : m_chessBoard->getBoard())
	{
		for (std::shared_ptr<ChessPiece> piece : row)
		{
			if (piece == nullptr || piece->getColor() == color)
				continue;
			std::shared_ptr<Capture> possibleCapture = std::make_shared<Capture>(piece->getSquare(), kingPos, piece, king);
			try
			{
				return possibleCapture->checkValidity(*this);
			}
			catch (const InvalidMove& invalid)
			{
				continue;
			}
		}
	}
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