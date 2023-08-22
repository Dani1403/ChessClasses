#include "ChessGame.h"
#include <iostream>

int main()
{
	ChessGame game;
	try {
		game.initBoard();
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	return 0;
}