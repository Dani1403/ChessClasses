#pragma once
#include "../utilities.h"
#include "../Pieces/ChessPiece.h"

class ChessGame;

class ChessMove
{
public:
	ChessMove(const Square& source, const Square& destination, std::shared_ptr<ChessPiece> pieceToMove) :
		m_source(source), m_destination(destination), m_pieceToMove(pieceToMove) {}
	virtual ~ChessMove() = default;

	/*
	* return a string containing all the information for a specific move
	*/
	virtual std::string moveDescription() const;

	/* Getters */
	Square getSource() const { return m_source; }
	Square getDest() const { return m_destination; }
	std::shared_ptr<ChessPiece> getPieceToMove() const { return m_pieceToMove; }

	/* Setters */
	void setSource(const Square& newSource) { m_source = newSource; }
	void setDest(const Square& newDestination) { m_destination = newDestination; }
	void setPieceToMove(std::shared_ptr<ChessPiece> newPieceToMove) { m_pieceToMove = newPieceToMove; }

	/*
	* checks if a regular move is valid
	* checks for :
	*	- color of the piece to move is the color of the current player
	*	- there is a valid movement for this piece between source and destination
	* - there is no piece at the destination
	*	- there is no obstacle between the source and the destination
	* - > raise the appropriate exception in case of invalid move
	*/
	virtual bool checkValidity(ChessGame& game) const;


	/* Uses checkValidity to check if a move is possible
	 * @param game : the game to check the move on
	 * @return true if the move is possible, false otherwise
	 * Use this function when you don't want to handle the exceptions
	 */
	bool checkPossibleMove(ChessGame& game);


	/*
	* apply the move to the current game
	*	@param game : the game to apply the move to
	*	@return true if the move was applied, false otherwise
	*/
	virtual bool execute(ChessGame& game) const;
	//virtual void updatePieces();

	/*
	 * undo the move on the current game
	 * @param game : the game to undo the move on
	 */
	virtual void undo(ChessGame& game) const;

	/*
	 * equality operator for a move
	 * @param other : the move to compare to
	 * @return true if the moves are equal, false otherwise
	 */
	bool operator==(const ChessMove& other) const;

protected:
	Square m_source, m_destination;
	std::shared_ptr<ChessPiece> m_pieceToMove;
};

/*
 * output operator for a move
 * @param os : the output stream
 * @param move : the move to output
 * @return the output stream
 */
std::ostream& operator<<(std::ostream& os, const ChessMove& move);
