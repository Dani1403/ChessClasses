#pragma once
#include "Player.h"
#include "ChessBoard.h"
#include "Pieces/ChessPiece.h"
#include "Pieces/Queen.h"
#include "Pieces/Bishop.h"
#include "Pieces/King.h"
#include "Pieces/Knight.h"
#include "Pieces/Pawn.h"
#include "Pieces/Rook.h"
#include "Moves/ChessMove.h"
#include "Moves/Capture.h"

class ChessGame
{
public:
	ChessGame() {}
	~ChessGame() {}

	ChessBoard* getChessBoard() { return m_chessBoard; }

	void initBoard();
	void play();

	void makeMove(ChessMove* move);
	void undo();

	bool isInCheck(Color color);
	bool isInCheckmate(Color color);
	bool isStaleMate();
	bool isGameOver();

private:
	ChessBoard* m_chessBoard;
	std::vector<ChessMove*> m_moves;
	std::vector<Player> m_players;
	Player m_currentPlayer;

	void addPieces(ChessBoard* board, Color color);
	void addPawns(ChessBoard* board, Color color);
};