#include "ChessGame.h"
#include <iostream>

int main()
{
	try {
		ChessGame game;
		std::shared_ptr<ChessBoard> board = game.getChessBoard();
		std::shared_ptr<ChessPiece> pawn = board->getPieceAt({ 1,0 });
		std::shared_ptr<ChessMove> move = std::make_shared<ChessMove>(ChessMove({ 1,0 }, { 2 ,0 }, pawn));
		game.makeMove(move);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	std::cout << "Compilation successful";
	return 0;
}