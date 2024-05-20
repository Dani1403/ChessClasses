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

	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Chess++");
	auto image = sf::Image();
	if (image.loadFromFile("src/img/Chess_kdt45.png"))
		window.setIcon(ICON_SIZE, ICON_SIZE, image.getPixelsPtr());
	try
	{
		ChessGame game(window);
		game.play();
	}
	catch (const ExitGame&)
	{
		drawMessage(window, EXIT_MESSAGE);
		window.display();
		window.close();
	}
	return 0;
}