#include "Game.hpp"

enum Button
{
	START,
	QUIT,
	PUSHW,
	MENU
};

Game::Game()
{
	m_wall = nullptr;
	m_timer = nullptr;
	m_rend = nullptr;
	m_music = nullptr;

	m_isRunning = true;
	restart();
}

// Inits SDL, the wall, the render manager and the timer (also starts the timer)
void Game::init(const char* _title, int _xpos, int _ypos)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		cout << "Init sucessfull" << endl;

		m_rend = new RenderMng(_title, _xpos, _ypos);
		m_music = new MusicMng();
		m_wall = new Wall();

		m_timer = new Timer();
		m_isRunning = true;
	}
}

void Game::restart()
{
	m_isPaused = false;
	m_isLost = false;
	m_currScore = 0;
	m_currStage = 1;
	m_push_intv = PSH_INTV;
	m_max_stg_pts = STG_PTS;
	m_stg_prog = 0;

	m_isMultiBomb = false;
	m_MBombType = 0;
	m_isAimBomb = false;
	m_ABomb_clicks = 0;

	if (m_timer != nullptr)
	{
		m_timer->stop();
	}
	if (m_wall != nullptr)
	{
		m_wall->clearWall();
	}
}

// Handles window events and mouse clicks
void Game::handleEvent()
{
	SDL_Event e;
	SDL_PollEvent(&e);

	switch (e.type)
	{
	case SDL_QUIT:
		m_isRunning = false;
		break;

	case SDL_KEYDOWN:
		if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE && m_gameStarted)
		{
			m_isPaused = !m_isPaused;
			if (m_isPaused)
			{
				m_timer->pause();
				m_music->pause();
			}
			else
			{
				m_timer->unpause();
				m_music->resume();
			}		  
		}
		break;

	case SDL_MOUSEBUTTONDOWN:
		if (!m_gameStarted)
		{
			m_isRunning = (!clickedButton(e.button.x, e.button.y, QUIT));

			if (clickedButton(e.button.x, e.button.y, START))
			{
				restart();
				m_wall->initWall();
				m_timer->start();
				m_gameStarted = true;
			}
		}
		else
		{
			if (m_isLost)
			{
				if (clickedButton(e.button.x, e.button.y, MENU))
				{
					m_gameStarted = false;
				}
			}
			else 
			{
				if (m_wall != nullptr)
				{
					if (!m_isPaused)
					{
						int block_type = 0;

						// Grid [r][c] click location
						int _row = (e.button.y - WALL_Y1) / B_HEIGHT;
						int _col = (e.button.x - WALL_X1) / B_WIDTH;

						// If clicked inside the wall save the block type
						if (_row >= 0 && _row < NROW && _col >= 0 && _col < NCOL)
						{
							block_type = m_wall->getWall().wallMx[_row][_col];

							// Not currently in click bomb so click bomb or ore
							if (!m_isMultiBomb && !m_isAimBomb)
							{
								// If the clicked location is an ore
								if (block_type <= 5)
								{
									deleteOres(_row, _col, block_type);
								}
								// If its a bomb
								else
								{
									deleteBomb(_row, _col, block_type);
								}
							}
							// Currently in click bomb 
							else
							{
								// Multi color bomb - deletes all equal to clicked
								if (m_isMultiBomb)
								{
									int click_score = 0;
									if (block_type > 0 && block_type <= 5)
									{
										for (int i = 0; i <= NROW; i++)
										{
											for (int j = 0; j <= NCOL; j++)
											{
												if (m_wall->getWall().wallMx[i][j] == block_type)
												{
													click_score++;
													m_wall->setBlock(i, j, 0);
												}
											}
										}

										m_currScore += (click_score * 10);
										m_stg_prog += (click_score * 10);
										m_isMultiBomb = false;
									}
								}
								// Aim bomb - deletes all clicked
								if (m_isAimBomb)
								{
									if (block_type > 0 && block_type <= 5)
									{
										m_wall->setBlock(_row, _col, 0);
										m_ABomb_clicks++;
									}
									if (m_ABomb_clicks >= AIM_CLICKS)
									{
										m_currScore += (AIM_CLICKS * AIM_CLICKS);
										m_stg_prog += (AIM_CLICKS * AIM_CLICKS);
										m_isAimBomb = false;
										m_ABomb_clicks = 0;
									}
								}
							}
						}

						// Push wall button click
						if (clickedButton(e.button.x, e.button.y, PUSHW))
						{
							m_timer->stop();
							m_wall->pushWallLeft();
							m_timer->start();
						}
					}
				}
			}
		}
		break;
	default:
		break;
	}
}

// Updates game logic
void Game::update()
{
	m_music->start();

	if (m_gameStarted || !m_isPaused || !m_isLost)
	{
		// Push the wall each interval and restarts timer
		if (m_timer->getTicks() > (Uint32)m_push_intv)
		{
			m_timer->stop();
			m_wall->pushWallLeft();
			m_timer->start();
		}
		// Loosing condition - a block reached the start of the grid
		if (m_wall->getWall().wallMx[NROW - 1][0] != 0 && !m_isLost)
		{
			m_rend->setFinalScore(m_currScore);
			m_isLost = true;
		}
		// Different stage every x score. Having a stage progress and current score allows for easier
		// HUD stage bar size calculation
		if (m_stg_prog > m_max_stg_pts)
		{
			m_music->levelUp();
			m_currStage++;
			m_max_stg_pts += 10;
			m_stg_prog = 0;
			m_push_intv -= 100;
			m_wall->initWall();
		}
	}
}

// Updates game graphics
void Game::render()
{
	SDL_RenderClear(m_rend->getRenderer());

	m_rend->renderBg();

	if (!m_gameStarted)
	{
		m_rend->renderMenu();
	}
	else
	{
		if(m_isLost)
		{
			m_music->stop();
			m_rend->renderLostScreen();
		}
		else
		{
			if (m_isPaused)
			{
				m_rend->renderPauseScreen();
			}
			else
			{
				// Renders wall and grid, timer, score, and curr. stage
				m_rend->renderGame(&m_wall->getWall());
				m_rend->renderHUD(m_timer->getTicks(), m_push_intv, m_currScore, m_stg_prog, m_currStage, m_max_stg_pts);

				if (m_isMultiBomb)
				{
					m_rend->renderMultiBomb();
				}
				if (m_isAimBomb)
				{
					m_rend->renderAimBomb(AIM_CLICKS - m_ABomb_clicks);
				}
			}
		}
	}

	SDL_RenderPresent(m_rend->getRenderer());
}

void Game::clean()
{
	m_rend->~RenderMng();
	m_timer->~Timer();
	m_music->~MusicMng();

	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

// Checks if the click coordinates are inside the bt button
bool Game::clickedButton(Sint32 _mouseX, Sint32 _mouseY, int bt)
{
	switch (bt)
	{
	case START:
		return _mouseX >= START_BT_X && _mouseX <= START_BT_X + BTN_WIDTH
			&& _mouseY >= START_BT_Y && _mouseY <= START_BT_Y + BTN_HEIGHT;
		break;

	case QUIT:
		return _mouseX >= QUIT_BT_X && _mouseX <= QUIT_BT_X + BTN_WIDTH
			&& _mouseY >= QUIT_BT_Y && _mouseY <= QUIT_BT_Y + BTN_HEIGHT;
		break;

	case PUSHW:
		return _mouseX >= NSB_BT_X && _mouseX <= NSB_BT_X + B_WIDTH
			&& _mouseY >= NSB_BT_Y && _mouseY <= NSB_BT_Y + B_HEIGHT;
		break;

	case MENU:
		return _mouseX >= MENU_BT_X && _mouseX <= MENU_BT_X + BTN_WIDTH
			&& _mouseY >= MENU_BT_Y && _mouseY <= MENU_BT_Y + BTN_HEIGHT;
	default:
		return false;
		break;
	}
}

// Deletes grouped blocks by calling DFS, adds to score and a bomb if the group is big enough
// The bomb will have its corresponding type
void Game::deleteOres(int _row, int _col, int _btype)
{
	// Does the DFS search and deletes the blocks
	int click_score = m_wall->dfsDelete(_row, _col);

	m_currScore += (click_score * click_score);
	m_stg_prog += (click_score * click_score);

	// If a group of 5 or more is deleted
	if (click_score > 4)
	{
		// A bomb is created in its place, with the corresponding type
		m_wall->setBlock(_row, _col, (_btype + 5));
	}
}

// Deletes blocks with a bomb, or activates the click mode if its the case
void Game::deleteBomb(int _row, int _col, int _btype)
{
	int click_score = m_wall->explodeBomb(_row, _col, _btype);
	// If the bomb already exploded
	if (click_score >= 0)
	{
		m_currScore += (click_score * click_score);
		m_stg_prog += (click_score * click_score);
	}
	// Click bombs
	else
	{
		if (click_score == -1)
		{
			m_isMultiBomb = true;
			m_wall->setBlock(_row, _col, 0);
		}
		else if (click_score == -2)
		{
			m_isAimBomb = true;
			m_wall->setBlock(_row, _col, 0);
		}
	}
}


