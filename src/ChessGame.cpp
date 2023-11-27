#include "ChessGame.h"

#include "Moves/EnPassant.h"

#define DEBUG_STALEMATE 


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


bool ChessGame::isInCheck(const Color color)
{
	Square kingPos = m_chessBoard->getKingPosition(color);
	std::shared_ptr<ChessPiece> king = m_chessBoard->getPieceAt(kingPos);
	moveToNextPlayer();
	for (const auto& row : m_chessBoard->getBoard())
	{
		for (const auto& piece : row)
		{
			if (piece == nullptr || piece->getColor() == color)
				continue;
			const auto possibleCapture = std::make_shared<Capture>(piece->getSquare(), kingPos, piece, king);
			if (possibleCapture->checkPossibleMove(*this))
			{
				moveToNextPlayer();
				return true;
			}
		}
	}
	moveToNextPlayer();
	return false;
}

std::vector<std::shared_ptr<ChessMove>> ChessGame::getPossibleMovesForPiece(std::shared_ptr<ChessPiece> pieceToCheck)
{
	std::vector<std::shared_ptr<ChessMove>> possibleMoves;
	int intRow = 0, intCol = 0;
	for (auto& row : m_chessBoard->getBoard())
	{
		for (auto& piece : row)
		{
			const Square square = { intRow, intCol };
			if (piece)
			{
				std::shared_ptr<ChessMove> move = std::make_shared<Capture>(pieceToCheck->getSquare(), square, pieceToCheck, piece);
				if (move->checkPossibleMove(*this))
          possibleMoves.push_back(move);
			}

			std::shared_ptr<ChessMove> move = std::make_shared<ChessMove>(pieceToCheck->getSquare(), square, pieceToCheck);
			if (move->checkPossibleMove(*this))
        possibleMoves.push_back(move);

			std::shared_ptr<King> king = std::dynamic_pointer_cast<King>(pieceToCheck);
			if (king)
			{
				std::shared_ptr<ChessMove> castleKing = getCurrentPlayer().getCastle(*this, m_chessBoard, Side::KING);
				if (castleKing->checkPossibleMove(*this))
					possibleMoves.push_back(castleKing);
				std::shared_ptr<ChessMove> castleQueen = getCurrentPlayer().getCastle(*this, m_chessBoard, Side::QUEEN);
				if (castleQueen->checkPossibleMove(*this))
					possibleMoves.push_back(castleQueen);
			}

			std::shared_ptr<Pawn> pawn = std::dynamic_pointer_cast<Pawn>(pieceToCheck);
			if (pawn)
			{
				const Color color = pawn->getColor();
				std::shared_ptr<ChessMove> promotion = std::make_shared<Promotion>(pieceToCheck->getSquare(), square, pawn, getCurrentPlayer().getPromotedPiece(Type::QUEEN, color, { rowForPawnPromotion(color), pawn->colForPromotion() }));
        if (promotion->checkPossibleMove(*this))
          possibleMoves.push_back(promotion);
      }
			intCol = (intCol == 7) ? 0 : intCol + 1;
		}
		intRow++;
	}
	return possibleMoves;
}

bool ChessGame::checkPossibleMoves(std::vector<std::shared_ptr<ChessMove>> possibleMoves)
{
   for (const auto& move : possibleMoves)
  {
    move->execute(*this);
    if (!isInCheck(m_currentPlayer.getColor()))
    {
      move->undo(*this);
      return true;
    }
    move->undo(*this);
  }
  return false;
}

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
      const bool hasValidMove = checkPossibleMoves(possibleMoves);
			if (hasValidMove)
        return true;
		}
	}
	return false;
}


bool ChessGame::isInCheckmate(const Color color)
{
	if (!isInCheck(color))
		return false;
	return !colorHasValidMove(color);
}

bool ChessGame::isInStaleMate(const Color color)
{
   if (isInCheck(color))
    return false;
  return !colorHasValidMove(color);
}

bool ChessGame::isGameOver()
{
	/*
	* Ideally implemented with repetitions
	*/
#ifndef DEBUG_STALEMATE
	return isInCheckmate(Color::WHITE) || isInCheckmate(Color::BLACK) ||
	       isInStaleMate(Color::WHITE) || isInStaleMate(Color::BLACK);
#endif
  const bool final = isInCheckmate(Color::WHITE) || isInCheckmate(Color::BLACK);
	if (final)
		std::cout << "There is a checkmate" << std::endl;
	return final;
}

// MOVE AND PLAYER TURN LOGIC

void ChessGame::undo()
{
	if (m_moves.empty())
    return;
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
}


// MAIN LOOP 

void ChessGame::play()
{
	try
	{
		m_chessBoard->draw();
		while (!isGameOver())
		{
			playerTurn();
			moveToNextPlayer();
		}
	} catch (const std::exception& e)
	{
	     std::cout << e.what() << std::endl;
  }
}