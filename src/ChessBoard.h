#pragma once
#include "Pieces/ChessPiece.h"
#include "Pieces/King.h"

class ChessMove;

class ChessBoard
{
public:

	static const int BOARD_SIZE = 8;

	ChessBoard();

	void removePiece(std::shared_ptr<ChessPiece> piece);
	void addPiece(std::shared_ptr<ChessPiece> piece);
	void movePiece(std::shared_ptr<ChessPiece> piece, const Square& destination);
	bool checkObstacles(const ChessMove* move) const;

	std::array<std::array<std::shared_ptr<ChessPiece>, BOARD_SIZE>, BOARD_SIZE> getBoard() const { return m_board; }
	std::shared_ptr<ChessPiece> getPieceAt(const Square& square) const;
	Square getKingPosition(Color color);

private:
	std::array<std::array<std::shared_ptr<ChessPiece>, BOARD_SIZE>, BOARD_SIZE> m_board;

	std::map<Color, Square> m_kingPositions;

	bool checkRowForObstacle(const Square& src, const Square& dest) const;
	bool checkColForObstacle(const Square& src, const Square& dest) const;
	bool checkDiagForObstacle(const Square& src, const Square& dest) const;
	void addKingPosition(std::shared_ptr<King> king);
};