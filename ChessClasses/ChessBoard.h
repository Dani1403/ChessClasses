#pragma once
#include "Pieces/ChessPiece.h"

class ChessBoard
{	
	static const int BOARD_SIZE = 64;
public:
	ChessPiece* removePiece(ChessPiece* piece);
	bool addPiece(ChessPiece* piece);
	bool movePiece(ChessPiece* piece, const Square& source, const Square& destination);
}; 