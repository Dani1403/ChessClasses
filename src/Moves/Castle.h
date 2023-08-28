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

	bool execute(ChessGame& game) const override;
	void undo(ChessGame& game) const override;
private:
	Side m_side;
	std::shared_ptr<Rook> m_rookToMove;
	int offset() const { return m_side == Side::KING ? 2 : -2; }
	Square kingDest() { return { getPieceToMove()->getSquare().row, getPieceToMove()->getSquare().col + offset() }; };
	Square rookDest() { return { kingDest().row, kingDest().col - (offset() / 2) }; };
	ChessMove m_kingMove = ChessMove(getPieceToMove()->getSquare(), kingDest(), getPieceToMove());
	ChessMove m_rookMove = ChessMove(getRookToMove()->getSquare(), rookDest(), getRookToMove());
};

