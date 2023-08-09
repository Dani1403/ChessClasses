#pragma once
#include "Pieces/ChessPiece.h"

class ChessMove;

class ChessBoard
{	
public:
	virtual ~ChessBoard() {}
	virtual ChessPiece* removePiece(ChessPiece* piece) = 0;
	virtual bool addPiece(ChessPiece* piece) = 0;
	virtual bool movePiece(ChessPiece* piece, const Square& source, const Square& destination) = 0;
	virtual bool checkRowForObstacle(ChessMove* move) const = 0;
	virtual bool checkColForObstacle(ChessMove* move) const = 0;
	virtual bool checkDiagForObstacle(ChessMove* move) const = 0;
	virtual bool checkObstacles(ChessMove* move) const = 0;
}; 

class ChessBoardSingleton : public ChessBoard
{
	static const int BOARD_SIZE = 8;
	std::unique_ptr<ChessPiece> m_board[BOARD_SIZE][BOARD_SIZE];
	ChessBoardSingleton() 
	{
		for (int i = 0; i < BOARD_SIZE; i++)
		{
			for (int j = 0; j < BOARD_SIZE; j++)
				m_board[i][j] = nullptr;
		}
	}

public:
	static ChessBoardSingleton& getInstance()
	{
		static ChessBoardSingleton instance;
		return instance;
	}
	ChessPiece* removePiece(ChessPiece* piece) override;
	bool addPiece(ChessPiece* piece) override;
	bool movePiece(ChessPiece* piece, const Square& source, const Square& destination) override;
	bool checkRowForObstacle(ChessMove* move) const override;
	bool checkColForObstacle(ChessMove* move) const override;
	bool checkDiagForObstacle(ChessMove* move) const override;
	bool checkObstacles(ChessMove* move) const override;
};