#include "Player.h"
#include "Moves/ChessMove.h"
#include "Moves/Capture.h"
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
	std::string input = getMoveFromUser(std::cin);
	Square source = algebraicToSquare(input.substr(0, 2));
	Square destination = algebraicToSquare(input.substr(input.length() - 2));
	std::shared_ptr<ChessBoard> board = game.getChessBoard();
	std::shared_ptr<ChessPiece> pieceToMove = board->getPieceAt(source);
	if (input.at(2) == 'X')
	{
		std::shared_ptr<ChessPiece> capturedPiece = board->getPieceAt(destination);
		return std::make_shared<Capture>(source, destination, pieceToMove, capturedPiece);
	}
	return std::make_shared<ChessMove>(source, destination, pieceToMove);
}