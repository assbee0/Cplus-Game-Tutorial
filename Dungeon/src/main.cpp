#include	<SDL/SDL.h>
#include	<Game.h>

int main(int argc, char* argv[])
{
	Dungeon::Game game;
	bool success = game.Initialize();
	if (success)
	{
		game.Loop();
	}
	game.Shutdown();

	return 0;
}