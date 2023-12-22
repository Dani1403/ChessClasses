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
	ChessGame game;
  game.play();
  std::cout << EXIT_MESSAGE << std::endl;
	return 0;
}