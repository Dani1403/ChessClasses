#include "ChessGame.h"
#include <SFML/Graphics.hpp>


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
	sf::RenderWindow window(sf::VideoMode(1000, 1000), "Chess++");

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.display();
	}

	return 0;
	ChessGame game;
	game.play();
	std::cout << EXIT_MESSAGE << std::endl;
	return 0;
}