// Main loop

#include "Game.hpp"

Game* game = nullptr;

int main(int argc, char* argv[])
{
	game = new Game();
	game->init("Ores", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

	while (game->running())
	{
		game->handleEvent();
		game->update();
		game->render();
	}

	game->clean();

	return 0;
}

