#pragma once
#include "../Pieces/King.h"
#include "../Pieces/Rook.h"
#include "ChessMove.h"


class Castle : public ChessMove
{
public:

	/* Constructor */
	Castle(const Square& source, const Square& destination, std::shared_ptr<King> kingToMove, std::shared_ptr<Rook> rookToMove, Side side) :
		ChessMove(source, destination, kingToMove), m_rookToMove(rookToMove), m_side(side) {}

	/* Getters and Setters */
	std::shared_ptr<Rook> getRookToMove() const { return m_rookToMove; }

	/*
	* Checks if a castle move is valid
	* Checks for :
	* - the source square is not empty
	* - the color of the piece to move is the color of the current player
	* - the king and the rook have not moved yet
	* - there is no piece between the king and the rook
	* - the king is not in check
	* - TODO: the king does not pass through a square that is attacked by an enemy piece
	* - > raise the appropriate exception in case of invalid move
	*
	* @param game : the game to check the move on
	* @return true if the move is valid, otherwise an exception is raised
	* @override the ChessMove::checkValidity() function
	*/
	InvalidCause checkValidity(ChessGame& game) const override;

	/*
	* Apply the move to the current game
	* @param game : the game to apply the move to
	* @return true if the move was applied, false otherwise
	* @override the ChessMove::execute() function
	*/
	bool execute(ChessGame& game) const override;

	/*
	* Undo the move on the current game
	* @param game : the game to undo the move on
	* @override the ChessMove::undo() function
	*/
	void undo(ChessGame& game) const override;

	/*
	* @return a string describing the move
	* @override the ChessMove::moveDescription() function
	*/
	std::string moveDescription() const override;

private:
	std::shared_ptr<Rook> m_rookToMove;
	Side m_side;
	Square kingDest() const { return { getPieceToMove()->getSquare().row, getPieceToMove()->getSquare().col + offsetForCastle(m_side) }; };
	Square rookDest() const { return { kingDest().row, kingDest().col - (offsetForCastle(m_side) / 2) }; };
	ChessMove m_kingMove = ChessMove(getPieceToMove()->getSquare(), kingDest(), getPieceToMove());
	ChessMove m_rookMove = ChessMove(getRookToMove()->getSquare(), rookDest(), getRookToMove());
	std::vector<Square> squaresBetweenKingAndRook() const;
};

