#include "RenderManager.hpp"

RenderMng::RenderMng(const char* title, int xpos, int ypos)
{
	dstRect = SDL_Rect();
	srcRect = SDL_Rect();
	renderer = nullptr;
	timerFont = NULL;

	int fulls = 0;
	if (FULLSCREEN)
	{
		fulls = SDL_WINDOW_FULLSCREEN;
	}

	// Create window with information present on main.cpp
	window = SDL_CreateWindow(title, xpos, ypos, SCREEN_WIDTH, SCREEN_HEIGHT, fulls);
	if (window == NULL)
	{
		cout << "Error creating window: " << SDL_GetError() << endl;
		return;
	}

	// Create vsynced renderer for the created window
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL)
	{
		cout << "Error creating renderer: " << SDL_GetError() << endl;
		return;
	}
	else
	{
		// Set window to light grey
		SDL_SetRenderDrawColor(renderer, 209, 209, 209, 255);
	}

	// Init PNG loading
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		cout << "SDL Image init error :" << IMG_GetError() << endl;
		return;
	}

	//Init SDL_TTF
	if (TTF_Init() == -1)
	{
		cout << "SDL_TTF init error :" << TTF_GetError() << endl;
		return;
	}
	cout << "Renderer initiated" << endl;

	initTextures();
}

// Frees every block texture created and destroys renderer and window
RenderMng::~RenderMng()
{
	// Free block and text textures 
	for (auto x : blockTex)
	{
		x.free();
	}
	timerTex.free();

	// Free font
	TTF_CloseFont(timerFont);
	timerFont = nullptr;

	// Destroy window and renderer
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	renderer = nullptr;
	window = nullptr;
}

// Renders the grid and game wall (all blocks)
void RenderMng::renderGame(wallstrct* wall)
{
	render_grid();
	render_wall(wall);
}

// Renders the ticks given by the timer
void RenderMng::renderTimer(Uint32 currTime)
{
	// Black
	SDL_Color textColor = { 0, 0, 0 };
	// If loaded sucessfully
	if (!timerTex.loadFromText(to_string(currTime), textColor, timerFont))
	{
		cout << "Failed rendering text" << endl;
	}
	timerTex.render(400, 60);
}

// Inits the textures for the matrix blocks, one for each BTYPE and text
void RenderMng::initTextures()
{
	for (int i = 0; i < BTYPES; i++)
	{
		blockTex[i].setRend(renderer);
		blockTex[i].loadFromFile("assets/ore_" + to_string((i + 1)) + ".png");
	}

	//	Open the Font
	timerFont = TTF_OpenFont("assets/Action_Man.ttf", 28);
	if (timerFont == NULL)
	{
		cout << "Error loading font: " << TTF_GetError() << endl;
	}
	else
	{
		//Render text
		timerTex = WTexture(renderer);
	}
}

// Renders the wall - the matrix of blocks
void RenderMng::render_wall(wallstrct* wall)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	for (int i = 0; i < NROW; i++)
	{
		for (int j = 0; j < NCOL; j++)
		{
			int bType = wall->wallMx[i][j];
			if (bType != 0)
			{
				render_block(bType, i, j);
			}
		}
	}
}

// Renders a block with its position depending on the row and column and its size on the wall/matrix size
void RenderMng::render_block(int blockType, int row, int col)
{
	dstRect.h = B_HEIGHT;
	dstRect.w = B_WIDTH;

	dstRect.x = (col * B_WIDTH) + W_X0;
	dstRect.y = (row * B_HEIGHT) + W_Y0;

	blockTex[blockType - 1].render(dstRect);
}

// Draws a guiding grid
void RenderMng::render_grid()
{
	SDL_SetRenderDrawColor(renderer, 155, 155, 155, 255);

	for (int i = 0; i <= NCOL; i++)
	{
		SDL_RenderDrawLine(renderer, (i * B_WIDTH) + W_X0, W_Y0, (i * B_WIDTH) + W_X0, W_Y1);

		for (int j = 0; j <= NROW; j++)
		{
			SDL_RenderDrawLine(renderer, W_X0, (j * B_HEIGHT) + W_Y0, W_X1, (j * B_HEIGHT) + W_Y0);
		}
	}
}