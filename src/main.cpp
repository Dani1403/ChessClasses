#include "ChessGame.h"

int main()
{
	ChessGame game;
	try
	{
		game.play();
	} catch (const ExitGame&)
	{
	  std::cout << EXIT_MESSAGE << std::endl;
	}
	return 0;
}