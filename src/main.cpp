#include "ChessGame.h"

/*
* Entry Point of the program
*
* Creates a ChessGame object and calls the play() method
* play() method will run the game until the user quits or the game ends
*
* @return 0 if the program exits successfully
*/

int main()
{
	try
	{
		ChessGame game;
		sf::RenderWindow window(sf::VideoMode(1000, 1000), "Chess++");
		game.play(window);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	return 0;
}