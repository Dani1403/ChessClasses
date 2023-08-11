#pragma once
#include "Pieces/ChessPiece.h"

class ChessMove;

class ChessBoard
{	
public:
	virtual ~ChessBoard() {}
	virtual void removePiece(ChessPiece* piece) = 0;
	virtual void addPiece(ChessPiece* piece) = 0;
	virtual void movePiece(ChessPiece* piece, const Square& destination) = 0;
	virtual bool checkObstacles(const ChessMove* move) const = 0;
	virtual ChessPiece* getPieceAt(const Square& square) const = 0;
}; 

class ChessBoardSingleton : public ChessBoard
{
public:
	static ChessBoardSingleton& getInstance()
	{
		static ChessBoardSingleton instance;
		return instance;
	}
	void removePiece(ChessPiece* piece) override;
	void addPiece(ChessPiece* piece) override;
	void movePiece(ChessPiece* piece, const Square& destination) override;
	bool checkObstacles(const ChessMove* move) const override;
	ChessPiece* getPieceAt(const Square& square) const override;

	ChessBoardSingleton(const ChessBoardSingleton& other) = delete;
	ChessBoardSingleton& operator=(const ChessBoardSingleton& other) = delete;

private:
	static const int BOARD_SIZE = 8;
	ChessPiece* m_board[BOARD_SIZE][BOARD_SIZE];
	ChessBoardSingleton()
	{
		for (int i = 0; i < BOARD_SIZE; i++)
		{
			for (int j = 0; j < BOARD_SIZE; j++)
				m_board[i][j] = nullptr;
		}
	}

	bool checkRowForObstacle(const Square& src, const Square& dest) const;
	bool checkColForObstacle(const Square& src, const Square& dest) const;
	bool checkDiagForObstacle(const Square& src, const Square& dest) const;
};