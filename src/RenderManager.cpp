#include "RenderManager.hpp"

// Inits renderer, window and libs
RenderMng::RenderMng(const char* _title, int _xpos, int _ypos)
{
	m_dst_rect = SDL_Rect();
	m_src_rect = SDL_Rect();
	m_renderer = nullptr;
	m_timer_font = NULL;

	// Create window with information present on main.cpp
	m_window = SDL_CreateWindow(_title, _xpos, _ypos, SCREEN_WIDTH, SCREEN_HEIGHT, FULLSCREEN ? SDL_WINDOW_FULLSCREEN : 0);
	if (m_window == NULL)
	{
		cout << "Error creating window: " << SDL_GetError() << endl;
		return;
	}

	// Create vsynced renderer for the created window
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_renderer == NULL)
	{
		cout << "Error creating renderer: " << SDL_GetError() << endl;
		return;
	}
	else
	{
		// Set window to light grey
		SDL_SetRenderDrawColor(m_renderer, 209, 209, 209, 255);
	}

	// Init PNG loading
	int _imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(_imgFlags) & _imgFlags))
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
	// Free block, bombs, text and button textures 
	for (auto x : m_block_tex)
	{
		x.free();
	}

	for (auto x : m_bomb_tex)
	{
		x.free();
	}

	m_timer_tex.free();
	m_score_tex.free();
	m_stage_tex.free();
	m_nst_bttex.free();
	m_multiB_tex.free();
	m_aimB_tex.free();

	// Free font
	TTF_CloseFont(m_timer_font);
	m_timer_font = nullptr;

	// Destroy window and renderer
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	m_renderer = nullptr;
	m_window = nullptr;
}

// Inits the textures for the matrix blocks, one for each BTYPE and text
void RenderMng::initTextures()
{
	//Blocks
	for (int i = 0; i < BTYPES; i++)
	{
		m_block_tex[i].setRend(m_renderer);
		m_block_tex[i].loadFromFile("assets/ore_" + to_string((i + 1)) + ".png");

		m_bomb_tex[i].setRend(m_renderer);
		m_bomb_tex[i].loadFromFile("assets/bomb_" + to_string((i + 1)) + ".png");
	}

	//Button
	m_nst_bttex = WTexture(m_renderer);
	m_nst_bttex.loadFromFile("assets/pushw_b.png");

	//Open the Font
	m_timer_font = TTF_OpenFont("assets/Pacifico.ttf", 28);
	if (m_timer_font == NULL)
	{
		cout << "Error loading font: " << TTF_GetError() << endl;
	}
	else
	{
		//Render text
		m_timer_tex = WTexture(m_renderer);
		m_score_tex = WTexture(m_renderer);
		m_stage_tex = WTexture(m_renderer);
		m_multiB_tex = WTexture(m_renderer);
		m_aimB_tex = WTexture(m_renderer);
	}
}

// Renders the grid and game wall (all blocks)
void RenderMng::renderGame(wallstrct* m_wall)
{
	renderGrid();
	renderWall(m_wall);
	m_nst_bttex.setLoc(NSB_BT_X, NSB_BT_Y);
	m_nst_bttex.render();
}

// Renders the ticks given by the timer
void RenderMng::renderTimer(Uint32 _currTime)
{
	// Black
	SDL_Color _textColor = { 0, 0, 0 };
	// If loaded sucessfully
	if (!m_timer_tex.loadFromText(to_string(_currTime), _textColor, m_timer_font))
	{
		cout << "Failed rendering timer" << endl;
	}
	m_timer_tex.setLoc(TM_TXT_X, TM_TXT_Y);
	m_timer_tex.render();
}

// Renders the current game score
void RenderMng::renderScore(int _score)
{
	// Black
	SDL_Color _textColor = { 0, 0, 0 };
	// If loaded sucessfully
	if (!m_score_tex.loadFromText("Score: " + to_string(_score), _textColor, m_timer_font))
	{
		cout << "Failed rendering score" << endl;
	}
	m_score_tex.setLoc(SCR_TXT_X, SCR_TXT_Y);
	m_score_tex.render();
}

// Renders the current wall stage
void RenderMng::renderStage(int _stage)
{
	// Black
	SDL_Color _textColor = { 0, 0, 0 };
	// If loaded sucessfully
	if (!m_stage_tex.loadFromText("Stage: " + to_string(_stage), _textColor, m_timer_font))
	{
		cout << "Failed rendering stage" << endl;
	}
	m_stage_tex.setLoc(STG_TXT_X, STG_TXT_Y);
	m_stage_tex.render();
}

// Renders the info text of the multi bomb
void RenderMng::renderMultiBomb()
{
	// Black
	SDL_Color _textColor = { 0, 0, 0 };
	// If loaded sucessfully
	if (!m_multiB_tex.loadFromText("Click to delete all equals", _textColor, m_timer_font))
	{
		cout << "Failed rendering multi bomb text" << endl;
	}
	m_multiB_tex.setLoc(MBOMB_TXT_X, MBOMB_TXT_Y);
	m_multiB_tex.render();
}

// Renders the info text of the aim bomb
void RenderMng::renderAimBomb(int _clicks)
{
	// Black
	SDL_Color _textColor = { 0, 0, 0 };
	// If loaded sucessfully
	if (!m_aimB_tex.loadFromText("Clicks left: " + to_string(_clicks), _textColor, m_timer_font))
	{
		cout << "Failed rendering aim bomb text" << endl;
	}
	m_aimB_tex.setLoc(ABOMB_TXT_X, ABOMB_TXT_Y);
	m_aimB_tex.render();
}

// Renders the wall - the matrix of blocks
void RenderMng::renderWall(wallstrct* _wall)
{
	SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);

	for (int i = 0; i < NROW; i++)
	{
		for (int j = 0; j < NCOL; j++)
		{
			int _bType = _wall->wallMx[i][j];
			if (_bType != 0)
			{
				renderBlock(_bType, i, j);
			}
		}
	}
}

// Renders a block with its position depending on the row and column and its size on the wall/matrix size
void RenderMng::renderBlock(int _bT, int _row, int _col)
{
	// If the block type is 1-5 render an ore, else render a bomb 
	if (_bT <= BTYPES)
	{
		m_block_tex[_bT - 1].setLoc((_col * B_WIDTH) + WALL_X1, (_row * B_HEIGHT) + WALL_Y1);
		m_block_tex[_bT - 1].render();
	}
	else
	{
		m_bomb_tex[_bT - (BTYPES + 1)].setLoc((_col * B_WIDTH) + WALL_X1, (_row * B_HEIGHT) + WALL_Y1);
		m_bomb_tex[_bT - (BTYPES + 1)].render();
	}
}

// Draws a guiding grid
void RenderMng::renderGrid()
{
	SDL_SetRenderDrawColor(m_renderer, 155, 155, 155, 255);

	for (int i = 0; i <= NCOL; i++)
	{
		SDL_RenderDrawLine(m_renderer, (i * B_WIDTH) + WALL_X1, WALL_Y1, (i * B_WIDTH) + WALL_X1, WALL_Y2);

		for (int j = 0; j <= NROW; j++)
		{
			SDL_RenderDrawLine(m_renderer, WALL_X1, (j * B_HEIGHT) + WALL_Y1, WALL_X2, (j * B_HEIGHT) + WALL_Y1);
		}
	}
}