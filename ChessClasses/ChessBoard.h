#pragma once
#include "Pieces/ChessPiece.h"

class ChessBoard
{	
	static const int BOARD_SIZE = 64;
public:
	ChessPiece* removePiece(const ChessPiece& piece);
	bool addPiece(const ChessPiece& piece);
	bool movePiece(const ChessPiece& piece, const Square& source, const Square& destination);
};