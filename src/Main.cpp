// Main game loop.

#include "Game.hpp"

Game* game = nullptr;

int main(int argc, char* argv[])
{
	game = new Game();
	game->init("City Ores", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

	while (game->running())
	{
		game->handleEvent();			// Handles mouse and window events
		game->update();					// Updates game logic
		game->render();					// Updates screen
	}

	game->clean();						// Cleans renderer and closes game

	return 0;
}

