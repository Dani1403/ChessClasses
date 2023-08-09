#pragma once
#include "Pieces/ChessPiece.h"

class ChessMove;

class ChessBoard
{	
public:
	virtual ~ChessBoard() {}
	virtual void removePiece(std::unique_ptr<ChessPiece> piece) = 0;
	virtual void addPiece(std::unique_ptr<ChessPiece> piece) = 0;
	virtual void movePiece(std::unique_ptr<ChessPiece> piece, const Square& destination) = 0;
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

	bool checkRowForObstacle(const Square& src, const Square& dest) const;
	bool checkColForObstacle(const Square& src, const Square& dest) const;
	bool checkDiagForObstacle(const Square& src, const Square& dest) const;

public:
	static ChessBoardSingleton& getInstance()
	{
		static ChessBoardSingleton instance;
		return instance;
	}
	void removePiece(std::unique_ptr<ChessPiece> piece) override;
	void addPiece(std::unique_ptr<ChessPiece> piece) override;
	void movePiece(std::unique_ptr<ChessPiece> piece, const Square& destination) override;
	bool checkObstacles(ChessMove* move) const override;

	ChessBoardSingleton(const ChessBoardSingleton& other) = delete;
	ChessBoardSingleton& operator=(const ChessBoardSingleton& other) = delete;
};