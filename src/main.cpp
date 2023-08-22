#include "ChessGame.h"
#include <iostream>

int main()
{
	ChessBoard board;
	try {
		board.addPiece(std::make_shared<Pawn>(Pawn(Color::BLACK, { 1, 1 })));
		board.addPiece(std::make_shared<Pawn>(Pawn(Color::BLACK, { 1, 2 })));
		std::cout << *(board.getBoard()[1][1]);
		std::cout << *(board.getBoard()[1][2]);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	return 0;
}