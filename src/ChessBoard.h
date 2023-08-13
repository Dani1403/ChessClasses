#pragma once
#include "Pieces/ChessPiece.h"

class ChessMove;

class ChessBoard
{
public:

	ChessBoard()
	{
		for (int i = 0; i < BOARD_SIZE; i++)
		{
			for (int j = 0; j < BOARD_SIZE; j++)
				m_board[i][j] = nullptr;
		}
	}

	void removePiece(ChessPiece* piece);
	void addPiece(ChessPiece* piece);
	void movePiece(ChessPiece* piece, const Square& destination);
	bool checkObstacles(const ChessMove* move) const;
	ChessPiece* getPieceAt(const Square& square) const;

private:
	static const int BOARD_SIZE = 8;
	ChessPiece* m_board[BOARD_SIZE][BOARD_SIZE];

	bool checkRowForObstacle(const Square& src, const Square& dest) const;
	bool checkColForObstacle(const Square& src, const Square& dest) const;
	bool checkDiagForObstacle(const Square& src, const Square& dest) const;
};