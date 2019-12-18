#include "RenderManager.hpp"

// Inits renderer, window and libs
RenderMng::RenderMng(const char* _title, int _xpos, int _ypos)
{
	m_final_sc = 0;
	m_timer_rect = {};
	m_stage_rect = {};
	m_renderer = nullptr;
	m_game_font = nullptr;
	m_paused_font = nullptr;
	m_lost_font = nullptr;

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
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Linear texture filtering not enabled!");
		}
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
	initTextures();
}

// Frees every block texture created and destroys renderer and window
RenderMng::~RenderMng()
{
	// Free block, bombs, text and button textures 
	for (auto x : m_ore_tex)
	{
		x.free();
	}

	for (auto x : m_bomb_tex)
	{
		x.free();
	}

	m_backg_tex.free();
	m_timer_tex.free();
	m_score_tex.free();
	m_stage_tex.free();
	m_pushw_bt.free();
	m_endzone_tex.free();

	m_multiB_bt.free();
	m_aimB_bt.free();
	
	m_lost1_tex.free();
	m_lost2_tex.free();
	m_menuB_bt.free();
	m_paused_tex.free();
	m_start_bt.free();
	m_quit_bt.free();

	// Free font
	TTF_CloseFont(m_game_font);
	m_game_font = nullptr;
	TTF_CloseFont(m_paused_font);
	m_paused_font = nullptr;
	TTF_CloseFont(m_lost_font);
	m_lost_font = nullptr;

	// Destroy window and renderer
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	m_renderer = nullptr;
	m_window = nullptr;
}

// Inits the textures for the matrix blocks, one for each BTYPE and text
void RenderMng::initTextures()
{
	//Background
	m_backg_tex = WTexture(m_renderer);
	m_backg_tex.loadFromFile("assets/background.png");

	//Ores and bombs - This cycle works because there are equal number of bombs and ores types
	for (int i = 0; i < BTYPES; i++)
	{
		m_ore_tex[i].setRend(m_renderer);
		m_ore_tex[i].loadFromFile("assets/ore_" + to_string((i + 1)) + ".png");

		m_bomb_tex[i].setRend(m_renderer);
		m_bomb_tex[i].loadFromFile("assets/bomb_" + to_string((i + 1)) + ".png");
	}

	//Buttons
	m_pushw_bt = WTexture(m_renderer);
	m_pushw_bt.loadFromFile("assets/pushw_b.png");

	m_start_bt = WTexture(m_renderer);
	m_start_bt.loadFromFile("assets/start_b.png");

	m_quit_bt = WTexture(m_renderer);
	m_quit_bt.loadFromFile("assets/quit_b.png");

	m_menuB_bt = WTexture(m_renderer);
	m_menuB_bt.loadFromFile("assets/menu_b.png");

	//Open the Font
	m_game_font = TTF_OpenFont("assets/Pacifico.ttf", 30);
	m_paused_font = TTF_OpenFont("assets/Pacifico.ttf", 190);
	m_lost_font = TTF_OpenFont("assets/Pacifico.ttf", 90);
	if (m_game_font == NULL || m_paused_font == NULL || m_lost_font == NULL)
	{
		cout << "Error loading font: " << TTF_GetError() << endl;
	}
	else
	{
		//Render text
		m_lost1_tex = WTexture(m_renderer);
		m_lost2_tex = WTexture(m_renderer);
		m_paused_tex = WTexture(m_renderer);
		m_timer_tex = WTexture(m_renderer);
		m_score_tex = WTexture(m_renderer);
		m_stage_tex = WTexture(m_renderer);
		m_endzone_tex = WTexture(m_renderer);
		m_multiB_bt = WTexture(m_renderer);
		m_aimB_bt = WTexture(m_renderer);
	}
}

// Renders the background image
void RenderMng::renderBg()
{
	m_backg_tex.setLoc(0, 0);
	m_backg_tex.render();
}

// Initial menu - start and quit buttons
void RenderMng::renderMenu()
{
	m_start_bt.setLoc(START_BT_X, START_BT_Y);
	m_start_bt.render();

	m_quit_bt.setLoc(QUIT_BT_X, QUIT_BT_Y);
	m_quit_bt.render();
}

// Lost screen
void RenderMng::renderLostScreen()
{
	// White
	SDL_Color _textColor = { 255, 255, 255, 255 };

	if (!m_lost1_tex.loadFromText("You Lost!", _textColor, m_lost_font))
	{
		cout << "Failed rendering paused text" << endl;
	}
	m_lost1_tex.setLoc(YLOST_TXT_X, YLOST_TXT_Y);
	m_lost1_tex.render();

	if (!m_lost2_tex.loadFromText("Final Score: " + to_string(m_final_sc), _textColor, m_lost_font))
	{
		cout << "Failed rendering paused text" << endl;
	}
	m_lost2_tex.setLoc(FSCR_TXT_X, FSCR_TXT_Y);
	m_lost2_tex.render();

	m_menuB_bt.setLoc(MENU_BT_X, MENU_BT_Y);
	m_menuB_bt.render();
}

// Pause screen
void RenderMng::renderPauseScreen()
{
	// White
	SDL_Color _textColor = { 255, 255, 255 };

	if (!m_paused_tex.loadFromText("Paused...", _textColor, m_paused_font))
	{
		cout << "Failed rendering paused text" << endl;
	}
	m_paused_tex.setLoc(PAUSED_TXT_X, PAUSED_TXT_Y);
	m_paused_tex.render();
}

// Grid and game wall (all blocks)
void RenderMng::renderGame(wallstrct* m_wall)
{
	renderGrid();
	renderWall(m_wall);
	m_pushw_bt.setLoc(NSB_BT_X, NSB_BT_Y);
	m_pushw_bt.render();
}

// Timer text and bar, score and stage
void RenderMng::renderHUD(Uint32 currTime, int max_time, int currScore, int stg_prog, int stage, int max_stg_pts)
{
	// White
	SDL_Color _textColor = { 255, 255, 255, 255};

	if (!m_timer_tex.loadFromText("Push: ", _textColor, m_game_font))
	{
		cout << "Failed rendering timer" << endl;
	}
	m_timer_tex.setLoc(TM_TXT_X, TM_TXT_Y);
	m_timer_tex.render();

	int barSize = TM_MAX_WIDTH - (((double)currTime/max_time) * TM_MAX_WIDTH);
	m_timer_rect = { TM_TXT_X+80, 20, barSize, 24 };
	SDL_SetRenderDrawColor(m_renderer, 97, 76, 255, 255);
	SDL_RenderFillRect(m_renderer, &m_timer_rect);

	if (!m_score_tex.loadFromText("Score: " + to_string(currScore), _textColor, m_game_font))
	{
		cout << "Failed rendering score" << endl;
	}
	m_score_tex.setLoc(SCR_TXT_X, SCR_TXT_Y);
	m_score_tex.render();


	if (!m_stage_tex.loadFromText("Stage: " + to_string(stage), _textColor, m_game_font))
	{
		cout << "Failed rendering stage" << endl;
	}
	m_stage_tex.setLoc(STG_TXT_X, STG_TXT_Y);
	m_stage_tex.render();

	barSize = STG_MAX_WIDTH - (((double)stg_prog / max_stg_pts) * STG_MAX_WIDTH);
	m_stage_rect = {STG_TXT_X + 120, 20, barSize, 24 };
	SDL_SetRenderDrawColor(m_renderer, 97, 76, 255, 255);
	SDL_RenderFillRect(m_renderer, &m_stage_rect);

}

// Info text of the multi bomb
void RenderMng::renderMultiBomb()
{
	// White
	SDL_Color _textColor = { 255, 255, 255, 255 };
	// If loaded sucessfully
	if (!m_multiB_bt.loadFromText("Click to delete all equals", _textColor, m_game_font))
	{
		cout << "Failed rendering multi bomb text" << endl;
	}
	m_multiB_bt.setLoc(MBOMB_TXT_X, MBOMB_TXT_Y);
	m_multiB_bt.render();
}

// Info text of the aim bomb
void RenderMng::renderAimBomb(int _clicks)
{
	// White
	SDL_Color _textColor = { 255, 255, 255, 255 };
	// If loaded sucessfully
	if (!m_aimB_bt.loadFromText("Clicks left: " + to_string(_clicks), _textColor, m_game_font))
	{
		cout << "Failed rendering aim bomb text" << endl;
	}
	m_aimB_bt.setLoc(ABOMB_TXT_X, ABOMB_TXT_Y);
	m_aimB_bt.render();
}

// Wall - the matrix of blocks
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

// Block with its position depending on the row and column
void RenderMng::renderBlock(int _bT, int _row, int _col)
{
	// If the block type is 1-5 render an ore, else render a bomb 
	if (_bT <= BTYPES)
	{
		m_ore_tex[_bT - 1].setLoc((_col * B_WIDTH) + WALL_X1, (_row * B_HEIGHT) + WALL_Y1);
		m_ore_tex[_bT - 1].render();
	}
	else
	{
		m_bomb_tex[_bT - (BTYPES + 1)].setLoc((_col * B_WIDTH) + WALL_X1, (_row * B_HEIGHT) + WALL_Y1);
		m_bomb_tex[_bT - (BTYPES + 1)].render();
	}
}

// Guiding grid and end zone text
void RenderMng::renderGrid()
{
	SDL_SetRenderDrawColor(m_renderer, 155, 155, 155, 255);

	for (int i = 0; i <= NCOL; i++)
	{
		if (i == 0) // 5 lines at the beggining to mark the end zone
		{
			SDL_RenderDrawLine(m_renderer, (i * B_WIDTH) + WALL_X1 - 2, WALL_Y1, (i * B_WIDTH) + WALL_X1 - 2, WALL_Y2);
			SDL_RenderDrawLine(m_renderer, (i * B_WIDTH) + WALL_X1 - 1, WALL_Y1, (i * B_WIDTH) + WALL_X1 - 1, WALL_Y2);
			SDL_RenderDrawLine(m_renderer, (i * B_WIDTH) + WALL_X1 + 1, WALL_Y1, (i * B_WIDTH) + WALL_X1 + 1, WALL_Y2);
			SDL_RenderDrawLine(m_renderer, (i * B_WIDTH) + WALL_X1 + 2, WALL_Y1, (i * B_WIDTH) + WALL_X1 + 2, WALL_Y2);
		}
		SDL_RenderDrawLine(m_renderer, (i * B_WIDTH) + WALL_X1, WALL_Y1, (i * B_WIDTH) + WALL_X1, WALL_Y2);

		for (int j = 0; j <= NROW; j++)
		{
			SDL_RenderDrawLine(m_renderer, WALL_X1, (j * B_HEIGHT) + WALL_Y1, WALL_X2, (j * B_HEIGHT) + WALL_Y1);
		}
	}

	// White
	SDL_Color _textColor = { 255, 255, 255, 255 };

	if (!m_endzone_tex.loadFromText("end zone", _textColor, m_game_font))
	{
		cout << "Failed rendering end zone" << endl;
	}
	m_endzone_tex.setLoc(WALL_X1 - (B_WIDTH+20), WALL_Y1 - (B_HEIGHT+20));
	m_endzone_tex.render();
}