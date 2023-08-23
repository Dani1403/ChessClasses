#include "ChessGame.h"
#include <iostream>

int main()
{
	try {
		ChessGame game;
		std::shared_ptr<ChessBoard> board = game.getChessBoard();
		std::shared_ptr<ChessPiece> pawn1 = board->getPieceAt({1,4});
		std::shared_ptr<ChessMove> move1 = std::make_shared<ChessMove>(ChessMove({ 1,4 },
			{ 3, 4 }, pawn1));
		game.makeMove(move1);
		std::shared_ptr<ChessPiece> pawn2 = board->getPieceAt({6,5});
		std::shared_ptr<ChessMove> move2 = std::make_shared<ChessMove>(ChessMove({ 6,5 },
			{4,5}, pawn2));
		game.makeMove(move2);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	std::cout << "Compilation successful";
	return 0;
}