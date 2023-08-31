#include "ChessGame.h"
#include <iostream>

int main()
{
	try {
		ChessGame game;

		std::shared_ptr<ChessBoard> board = game.getChessBoard();
		std::shared_ptr<ChessPiece> pawn1 = board->getPieceAt(algebraicToSquare("e2"));
		std::shared_ptr<ChessMove> move1 = std::make_shared<ChessMove>(ChessMove(algebraicToSquare("e2"), algebraicToSquare("e4"), pawn1));
		game.makeMove(move1);

		std::shared_ptr<ChessPiece> pawn2 = board->getPieceAt(algebraicToSquare("f7"));
		std::shared_ptr<ChessMove> move2 = std::make_shared<ChessMove>(ChessMove(algebraicToSquare("f7"), algebraicToSquare("f5"), pawn2));
		game.makeMove(move2);

		std::shared_ptr<ChessMove> capture = std::make_shared<Capture>(Capture(algebraicToSquare("e4"), algebraicToSquare("f5"), pawn1, pawn2));
		//std::cout << *capture << std::endl;
		game.makeMove(capture);

		//std::cout << (isOnSameDiag(algebraicToSquare("e4"), algebraicToSquare("f5")) ? "diag" : "no diag") << std::endl;
		std::cout << (pawn1->isValidCapture(algebraicToSquare("e4"), algebraicToSquare("f5")) ? "capture" : "no capture") << std::endl;

		//std::shared_ptr<ChessPiece> wQueen = board->getPieceAt(algebraicToSquare("d1"));
		//std::shared_ptr<ChessMove> check = std::make_shared<ChessMove>(ChessMove(algebraicToSquare("d1"),
		//	algebraicToSquare("h5"), wQueen));
		//game.makeMove(check);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	std::cout << "Compilation successful";
	return 0;
}