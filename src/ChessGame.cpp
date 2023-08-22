#include "ChessGame.h"

void ChessGame::addPawns(ChessBoard* board, Color color)
{
	int row = (color == Color::WHITE) ? 2 : 7;
	for (int i = 1; i <= board->BOARD_SIZE; i++)
	{
		board->addPiece(std::make_shared<Pawn>(Pawn(color, { row, i })));
	}
}

void ChessGame::addPieces(ChessBoard* board, Color color)
{
	addPawns(board, color);
	int row = (color == Color::WHITE) ? 1 : 8;
	board->addPiece(std::make_shared<Rook>(Rook(color, { row, 1 })));
	board->addPiece(std::make_shared<Knight>(Knight(color, { row, 2 })));
	board->addPiece(std::make_shared<Bishop>(Bishop(color, {row, 3})));
	board->addPiece(std::make_shared<Queen>(Queen(color, { row, 4 })));
	board->addPiece(std::make_shared<King>(King(color, { row, 5 })));
	board->addPiece(std::make_shared<Bishop>(Bishop(color, { row, 3 })));
	board->addPiece(std::make_shared<Knight>(Knight(color, { row, 2 })));
	board->addPiece(std::make_shared<Rook>(Rook(color, { row, 1 })));
}

void ChessGame::initBoard()
{
	addPieces(m_chessBoard, Color::WHITE);
	addPieces(m_chessBoard, Color::BLACK);
}

bool ChessGame::isInCheck(Color color)
{
	ChessBoard* board = getChessBoard();
	Square kingPos = board->getKingPosition(color);
	for (const auto& row : board->getBoard())
	{
		for (std::shared_ptr<ChessPiece> piece : row)
		{
			ChessMove capture = Capture(piece->getSquare(), kingPos, piece, board->getPieceAt(kingPos));
			if (capture.execute(*this)) 
			{
				capture.undo(*this);
				return true;
			}
		}
	}
	return false;
}

void ChessGame::makeMove(ChessMove* move)
{
	std::cout << "Applied" << move;
	m_moves.push_back(move);
	move->execute(*this);
}

void ChessGame::undo()
{
	ChessMove* move = m_moves.back();
	if (move != nullptr)
		move->undo(*this);
	m_moves.pop_back();
}