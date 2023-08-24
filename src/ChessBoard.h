#pragma once
#include "Pieces/ChessPiece.h"
#include "Pieces/Queen.h"
#include "Pieces/Bishop.h"
#include "Pieces/King.h"
#include "Pieces/Knight.h"
#include "Pieces/Pawn.h"
#include "Pieces/Rook.h"

class ChessMove;

/*
* TODO:
*		-  get Possible Regular / Capture / Castle / Promotion / En Passant
*		-  render simple board
*		-	 check move logic
*/

class ChessBoard
{
public:

	static const int BOARD_SIZE = 8;

	ChessBoard();
	void addInitialPieces(Color color);

	void removePiece(std::shared_ptr<ChessPiece> piece);
	void addPiece(std::shared_ptr<ChessPiece> piece);
	void movePiece(std::shared_ptr<ChessPiece> piece, const Square& destination);
	bool checkObstacles(std::shared_ptr<ChessMove> move) const;

	std::vector<std::shared_ptr<ChessMove>> getPossibleMoves(std::shared_ptr<ChessPiece> piece);


	std::array<std::array<std::shared_ptr<ChessPiece>, BOARD_SIZE>, BOARD_SIZE> getBoard() const { return m_board; }
	std::shared_ptr<ChessPiece> getPieceAt(const Square& square);
	Square getKingPosition(Color color);

private:
	std::array<std::array<std::shared_ptr<ChessPiece>, BOARD_SIZE>, BOARD_SIZE> m_board;

	std::map<Color, Square> m_kingPositions;

	bool checkRowForObstacle(const Square& src, const Square& dest) const;
	bool checkColForObstacle(const Square& src, const Square& dest) const;
	bool checkDiagForObstacle(const Square& src, const Square& dest) const;
	void addKingPosition(std::shared_ptr<King> king);
};