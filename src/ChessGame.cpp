#include "ChessGame.h"

#include "Moves/EnPassant.h"

ChessGame::ChessGame() : m_chessBoard(std::make_shared<ChessBoard>(ChessBoard()))
{
  displayWelcomeMessage();
	initBoard();
  initPlayers();
}

void ChessGame::initPlayers()
{
  Player player1, player2;
  player1.setColor(Color::WHITE);
  player2.setColor(Color::BLACK);
  player1.setName(player1.getNameFromUser(std::cin, Color::WHITE));
  player2.setName(player2.getNameFromUser(std::cin, Color::BLACK));
  m_players.push_back(player1);
  m_players.push_back(player2);
  m_currentPlayer = m_players.front();
  std::cout << "First player : " << m_currentPlayer.getName() << std::endl;
}


void ChessGame::initBoard()
{
	m_chessBoard->addInitialPieces(Color::WHITE);
	m_chessBoard->addInitialPieces(Color::BLACK);
}

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

bool ChessGame::isInCheck(const Color color)
{
	const Square kingPos = m_chessBoard->getKingPosition(color);
  moveToNextPlayer();
  const bool check = isSquareAttacked(kingPos, color);
  moveToNextPlayer();
  return check;
}

void ChessGame::appendMove(std::vector<std::shared_ptr <ChessMove>>& moves, std::shared_ptr<ChessMove> move)
{
	if (move->checkPossibleMove(*this))
		moves.push_back(move);
}

void ChessGame::appendRegular(std::vector<std::shared_ptr <ChessMove>>& moves, std::shared_ptr<ChessPiece> piece, Square square)
{
	std::shared_ptr<ChessMove> regularMove = std::make_shared<ChessMove>(piece->getSquare(), square, piece);
	appendMove(moves, regularMove);
}

void ChessGame::appendCapture(std::vector<std::shared_ptr <ChessMove>>& moves, std::shared_ptr<ChessPiece> piece, std::shared_ptr<ChessPiece> captured, Square square)
{
	std::shared_ptr<ChessMove> capture = std::make_shared<Capture>(piece->getSquare(), square, piece, captured);
	appendMove(moves, capture);
}

void ChessGame::appendPromotion(std::vector<std::shared_ptr<ChessMove>>& moves, std::shared_ptr<Pawn> pawn, Square square)
{
	const Color color = pawn->getColor();
	std::shared_ptr<ChessMove> promotion = std::make_shared<Promotion>(pawn->getSquare(), square, pawn, getCurrentPlayer().getPromotedPiece(Type::QUEEN, color, { rowForPawnPromotion(color), pawn->colForPromotion() }));
	appendMove(moves, promotion);
}

void ChessGame::appendCastle(std::vector<std::shared_ptr<ChessMove>>& moves)
{
	std::shared_ptr<ChessMove> castleKing = getCurrentPlayer().getCastle(*this, m_chessBoard, Side::KING);
	appendMove(moves, castleKing);
	std::shared_ptr<ChessMove> castleQueen = getCurrentPlayer().getCastle(*this, m_chessBoard, Side::QUEEN);
	appendMove(moves, castleQueen);
}

std::vector<std::shared_ptr<ChessMove>> ChessGame::getPossibleMovesForPiece(std::shared_ptr<ChessPiece> pieceToCheck)
{
	std::vector<std::shared_ptr<ChessMove>> possibleMoves;
	for (int row = 0; row < m_chessBoard->BOARD_SIZE; row++)
	{
		for (int col = 0; col < m_chessBoard->BOARD_SIZE; col++)
		{
			std::shared_ptr<ChessPiece> pieceToCapture = m_chessBoard->getPieceAt({ row, col });
			if (pieceToCapture)
				appendCapture(possibleMoves, pieceToCheck, pieceToCapture, {row, col});
			appendRegular(possibleMoves, pieceToCheck, {row, col});
			std::shared_ptr<King> king = std::dynamic_pointer_cast<King>(pieceToCheck);
			if (king)
				appendCastle(possibleMoves);
			std::shared_ptr<Pawn> pawn = std::dynamic_pointer_cast<Pawn>(pieceToCheck);
			if (pawn)
				appendPromotion(possibleMoves, pawn, {row, col});
		}
	}
	return possibleMoves;
}

bool ChessGame::checkPossibleMoves(const std::vector<std::shared_ptr<ChessMove>>& possibleMoves, Color color)
{
  for (auto move : possibleMoves)
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

bool ChessGame::colorHasValidMove(const Color color)
{
	for (int row = 0; row < m_chessBoard->BOARD_SIZE; row++)
	{
		for (int col = 0; col < m_chessBoard->BOARD_SIZE; col++)
		{
			std::shared_ptr<ChessPiece> piece = m_chessBoard->getPieceAt({row, col});
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
	bool stalemate = !colorHasValidMove(color);
	return stalemate;
}

bool ChessGame::isGameOver()
{
	const Color currentColor = m_currentPlayer.getColor();
	if (isInCheckmate(currentColor))
	{
		m_players.back().displayVictory();
		return true;
	} else if (isInStaleMate(currentColor))
	{
		std::cout << "Stalemate! " + colorToString(currentColor) + " has no legal move " << std::endl;
		return true;
	}
	moveToNextPlayer();
  if (isInCheckmate(opposite(currentColor)))
	{
		m_players.back().displayVictory();
		return true;
	} else if (isInStaleMate(opposite(currentColor)))
	{
		std::cout << "Stalemate! " + colorToString(opposite(currentColor)) + " has no legal move" << std::endl;
		return true;
	}
	moveToNextPlayer();
  return false;
}

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
		}
		catch (const InvalidMove& invalid)
		{
			std::cout << invalid.message() << std::endl << std::endl;
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