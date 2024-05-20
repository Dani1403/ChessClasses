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
		game.play();
	}
	catch (const ExitGame&)
	{
		return 0;
	}
	return 0;
}