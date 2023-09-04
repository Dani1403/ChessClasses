#include "Player.h"
#include "Moves/ChessMove.h"
#include "Moves/Capture.h"
#include "Moves/Castle.h"
#include "ChessBoard.h"
#include "ChessGame.h"

std::string Player::getMoveFromUser(std::istream& is) const
{
	displayInstructionToMove(std::cout);
	std::string input;
	is >> input;
	return input;
}

std::shared_ptr<ChessMove> Player::getMove(ChessGame& game) const
{
	std::shared_ptr<ChessBoard> board = game.getChessBoard();
	std::string input = getMoveFromUser(std::cin);
	if (input == CASTLE_KINGSIDE || input == CASTLE_QUEENSIDE)
	{
		Square source = board->getKingPosition(game.getCurrentPlayer().getColor());
		std::shared_ptr<ChessPiece> kingToMove = board->getPieceAt(source);
		std::shared_ptr<ChessPiece> rookToMove = board->getPieceAt({source.row, source.col + })
	}
	Square source = algebraicToSquare(input.substr(0, 2));
	Square destination = algebraicToSquare(input.substr(input.length() - 2));
	std::shared_ptr<ChessPiece> pieceToMove = board->getPieceAt(source);

	if (input.at(2) == CAPTURE_SYMBOL)
	{
		std::shared_ptr<ChessPiece> capturedPiece = board->getPieceAt(destination);
		return std::make_shared<Capture>(source, destination, pieceToMove, capturedPiece);
	}
	return std::make_shared<ChessMove>(source, destination, pieceToMove);
}