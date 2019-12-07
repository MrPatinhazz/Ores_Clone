// Main loop

#include "Game.hpp"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define FULLSCREEN false

Game* game = nullptr;

int main(int argc, char* argv[])
{
	game = new Game();
	game->init("Ores", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, FULLSCREEN);

	while (game->running())
	{
		game->handleEvent();
		game->update();
		game->render();
	}

	game->clean();

	return 0;
}
