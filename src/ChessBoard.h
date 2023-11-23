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
*/

class ChessBoard
{
public:

  static const int BOARD_SIZE = 8;

  ChessBoard();

  /*
   * Add the initial pieces to the board
   *  @param color - the color of the pieces to add
   */
  void addInitialPieces(Color color);

  /*
   * Draw the board with the pieces on it
   */
  void draw();

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
  Square getKingPosition(Color color);

private:
  std::array<std::array<std::shared_ptr<ChessPiece>, BOARD_SIZE>, BOARD_SIZE> m_board;

  std::map<Color, Square> m_kingPositions = {};

  bool checkRowForObstacle(const Square& src, const Square& dest) const;
  bool checkColForObstacle(const Square& src, const Square& dest) const;
  bool checkDiagForObstacle(const Square& src, const Square& dest) const;
  void addKingPosition(std::shared_ptr<King> king);
};