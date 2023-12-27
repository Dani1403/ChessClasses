#pragma once
#include "Pieces/Bishop.h"
#include "Pieces/ChessPiece.h"
#include "Pieces/King.h"
#include "Pieces/Knight.h"
#include "Pieces/Pawn.h"
#include "Pieces/Queen.h"
#include "Pieces/Rook.h"

class ChessMove;

class ChessBoard
{
public:

	static const int BOARD_SIZE = 8;

	/*
	* Constructor
	*/
	ChessBoard();

	/*
	* Add the initial pieces to the board
	*  @param color - the color of the pieces to add
	*/
	void addInitialPieces(const Color color);

	/*
	* Draw the board with the pieces on it to the console
	*/
	void draw() const;

	/*
	* Render the grid of the board
	* set the color of the squares to black or white
	* @param window - the window to render to
	*/
	void renderGrid(sf::RenderWindow& window) const;

	/*
	* Render the pieces on the board
	* @param window - the window to render to
	*/
	void renderPieces(sf::RenderWindow& window) const;

	/*
	* Render the indications of the columns
	* @param window - the window to render to
	*/
	void renderColIndications(sf::RenderWindow& window) const;

	/*
	* Render the indications of the rows
	* @param window - the window to render to
	*/
	void renderRowIndications(sf::RenderWindow& window) const;

	/*
	* Render the board with the pieces on it
	* @param window - the window to render to
	*/
	void render(sf::RenderWindow& window) const;

	/*
	* Remove a certain piece from the board
	* @param piece - the piece to remove
	*/
	void removePiece(std::shared_ptr<ChessPiece> piece);

	/*
	* Add a piece to the board
	* @param piece - the piece to add
	*/
	void addPiece(std::shared_ptr<ChessPiece> piece);

	/*
	* Move a piece to a certain square
	* @param piece - the piece to move
	* @param destination - the square to move the piece to
	*/
	void movePiece(std::shared_ptr<ChessPiece> piece, const Square& destination);

	/*
	* Check if there are obstacles between two squares
	* @param src - the source square
	* @param dest - the destination square
	* @return true if there are obstacles between the squares, false otherwise
	*/
	bool checkObstacles(const Square& src, const Square& dest) const;

	/*
	* Get the board
	* @return the board
	*/
	std::array<std::array<std::shared_ptr<ChessPiece>, BOARD_SIZE>, BOARD_SIZE> getBoard() const { return m_board; }

	/*
	* Get the piece at a certain square
	* @param square - the square to get the piece from
	* @return the piece at the square
	*/
	std::shared_ptr<ChessPiece> getPieceAt(const Square& square);

	/*
	* Get the king position of a certain color
	* @param color - the color of the king
	* @return the king position
	*/
	Square getKingPosition(const Color color);

private:
	std::array<std::array<std::shared_ptr<ChessPiece>, BOARD_SIZE>, BOARD_SIZE> m_board;

	std::map<Color, Square> m_kingPositions = {};

	/*
	* Check if there are obstacles between two squares on the same row
	* @param src - the source square
	* @param dest - the destination square
	* @return true if there are obstacles between the squares, false otherwise
	*/
	bool checkRowForObstacle(const Square& src, const Square& dest) const;

	/*
	* Check if there are obstacles between two squares on the same column
	* @param src - the source square
	* @param dest - the destination square
	* @return true if there are obstacles between the squares, false otherwise
	*/
	bool checkColForObstacle(const Square& src, const Square& dest) const;

	/*
	* Check if there are obstacles between two squares on the same diagonal
	* @param src - the source square
	* @param dest - the destination square
	* @return true if there are obstacles between the squares, false otherwise
	*/
	bool checkDiagForObstacle(const Square& src, const Square& dest) const;

	/*
	* Add the king's position to the map
	*/
	void addKingPosition(std::shared_ptr<King> king);
};