#include "ChessGame.h"

#include "Moves/EnPassant.h"

#define DEBUG_GET_MOVE

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
	bool emptyVector = possibleMoves.empty();
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
			Square square = { row, col };
			std::shared_ptr<ChessPiece> piece = m_chessBoard->getPieceAt({ row, col });
			if (piece == nullptr || piece->getColor() != color)
				continue;
			Type type = piece->getType();
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
#ifdef DEBUG_GET_MOVE
	const Color currentColor = m_currentPlayer.getColor();
	if (isInCheckmate(currentColor))
	{
		m_currentPlayer.displayVictory();
		return true;
	} else if (isInStaleMate(currentColor))
	{
		std::cout << "Stalemate! " + colorToString(currentColor) + " got the draw " << std::endl;
		return true;
	} else if (isInCheckmate(opposite(currentColor)))
	{
		m_players.back().displayVictory();
		return true;
	} else if (isInStaleMate(opposite(currentColor)))
	{
		std::cout << "Stalemate! " + colorToString(opposite(currentColor)) + " got the draw" << std::endl;
		return true;
	} else
		return false;
#endif // DEBUG
	return true;
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