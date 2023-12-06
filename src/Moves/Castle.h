#pragma once
#include "ChessMove.h"
#include "../Pieces/Rook.h"
#include "../Pieces/King.h"


class Castle : public ChessMove
{
public:
	Castle(const Square& source, const Square& destination, std::shared_ptr<King> kingToMove, std::shared_ptr<Rook> rookToMove, Side side) :
		ChessMove(source, destination, kingToMove), m_rookToMove(rookToMove), m_side(side)
	{}

	std::string moveDescription() const override;

	std::shared_ptr<Rook> getRookToMove() const { return m_rookToMove; }

	bool checkValidity(ChessGame& game) const override;
	bool execute(ChessGame& game) const override;
	void undo(ChessGame& game) const override;

private:
	std::shared_ptr<Rook> m_rookToMove;
	Side m_side;
	Square kingDest() const{ return { getPieceToMove()->getSquare().row, getPieceToMove()->getSquare().col + offsetForCastle(m_side) }; };
	Square rookDest() const { return { kingDest().row, kingDest().col - (offsetForCastle(m_side) / 2) }; };
	ChessMove m_kingMove = ChessMove(getPieceToMove()->getSquare(), kingDest(), getPieceToMove());
	ChessMove m_rookMove = ChessMove(getRookToMove()->getSquare(), rookDest(), getRookToMove());
};

