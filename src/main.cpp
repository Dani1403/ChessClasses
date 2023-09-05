#include "ChessGame.h"
#include <iostream>

int main()
{
	try {
		ChessGame game;
		game.play();
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	std::cout << "Compilation successful";
	return 0;
}