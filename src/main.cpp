#include "ChessGame.h"
#include <iostream>

int main()
{
	try {
		ChessGame game;
		std::shared_ptr<ChessBoard> board = game.getChessBoard();
		board->draw();
		std::shared_ptr<ChessPiece> pawn1 = board->getPieceAt({1,4});
		std::shared_ptr<ChessMove> move1 = std::make_shared<ChessMove>(ChessMove({ 1,4 },
			{ 3, 4 }, pawn1));
		game.makeMove(move1);
		board->draw();
		std::shared_ptr<ChessPiece> pawn2 = board->getPieceAt({6,5});
		std::shared_ptr<ChessMove> move2 = std::make_shared<ChessMove>(ChessMove({ 6,5 },
			{4,5}, pawn2));
		game.makeMove(move2);
		board->draw();
		std::shared_ptr<ChessPiece> wQueen = board->getPieceAt(algebraicToSquare("d1"));
		std::shared_ptr<ChessMove> check = std::make_shared<ChessMove>(ChessMove(algebraicToSquare("d1"),
			algebraicToSquare("h5"), wQueen));
		game.makeMove(check);
		board->draw();
		//std::string result = game.isInCheck(Color::BLACK) ? "Success" : "Fail";
		//std::cout << result << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	std::cout << "Compilation successful";
	return 0;
}