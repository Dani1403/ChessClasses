#include "ChessGame.h"
#include <iostream>

int main()
{
	try {
		ChessGame game;
		game.playerTurn();
		//std::shared_ptr<ChessBoard> board = game.getChessBoard();
		//std::shared_ptr<ChessPiece> pawn1 = board->getPieceAt(algebraicToSquare("e2"));
		//std::shared_ptr<ChessMove> move1 = std::make_shared<ChessMove>(ChessMove(algebraicToSquare("e2"), algebraicToSquare("e4"), pawn1));
		//game.makeMove(move1);

		//std::shared_ptr<ChessPiece> pawn2 = board->getPieceAt(algebraicToSquare("f7"));
		//std::shared_ptr<ChessMove> move2 = std::make_shared<ChessMove>(ChessMove(algebraicToSquare("f7"), algebraicToSquare("f5"), pawn2));
		//game.makeMove(move2);

		//std::shared_ptr<ChessMove> capture = std::make_shared<Capture>(Capture(algebraicToSquare("e4"), algebraicToSquare("f5"), pawn1, pawn2));
		//game.makeMove(capture);

		//std::shared_ptr<ChessPiece> knight = board->getPieceAt(algebraicToSquare("b8"));
		//std::shared_ptr<ChessMove> move3 = std::make_shared<ChessMove>(ChessMove(algebraicToSquare("b8"), algebraicToSquare("c6"), knight));
		//game.makeMove(move3);  
		//game.makeMove(move3); 

		//std::shared_ptr<ChessPiece> queen = board->getPieceAt(algebraicToSquare("d1"));
		//std::shared_ptr<ChessMove> check = std::make_shared<ChessMove>(ChessMove(algebraicToSquare("d1"), algebraicToSquare("h5"), queen));
		//game.makeMove(check);

		//std::cout << (isOnSameDiag(queen->getSquare(), board->getKingPosition(Color::BLACK)) ? "diag" : "no diag") << std::endl;

		////std::cout << game.isInCheck(opposite(game.getCurrentPlayer().getColor())) << std::endl;

		//std::shared_ptr<ChessMove> moveButCheck = std::make_shared<ChessMove>(ChessMove(algebraicToSquare("c6"), algebraicToSquare("b8"), knight));
		//game.makeMove(moveButCheck);

	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	std::cout << "Compilation successful";
	return 0;
}