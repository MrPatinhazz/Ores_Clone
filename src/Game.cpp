#include "Game.hpp"

Game::Game()
{
	m_currScore = 0;
	m_currStage = 1;
	m_wall = nullptr;
	m_timer = nullptr;
	m_rend = nullptr;
	m_isRunning = true;
}

Game::~Game()
{
}

// Inits SDL, the wall, the render manager and the timer
void Game::init(const char* _title, int _xpos, int _ypos)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		cout << "Init sucessfull" << endl;
		
		m_wall = new Wall();
		m_rend = new RenderMng(_title, _xpos, _ypos);	
		m_timer = new Timer();
		m_timer->start();

		m_isRunning = true;
	}
}

// Handles mouse clicks
void Game::handleEvent()
{
	SDL_Event e;
	SDL_PollEvent(&e);

	switch (e.type)
	{
	case SDL_QUIT:
		m_isRunning = false;
		break;

	case SDL_MOUSEBUTTONDOWN:
		if (m_wall != nullptr)
		{
			int _clickScore = 0;
			int _blockType = 0;
			int _row = (e.button.y - WALL_Y1) / B_HEIGHT;
			int _col = (e.button.x - WALL_X1) / B_WIDTH;

			// Type of block clicked
			_blockType = m_wall->getWall().wallMx[_row][_col];

			// Block clicks and added score if applied
			_clickScore = m_wall->deleteBlocks(_row,_col);
			if (_clickScore > 0)
			{
				m_currScore += (_clickScore*_clickScore);

				if (_clickScore > 4)
				{
					m_wall->setBlock(_row, _col, (_blockType + 5));
				}
			}

			// Push wall button click
			if (clickedPushW(e.button.x, e.button.y))
			{
				m_wall->pushWallLeft();
			}
		}
		break;
	default:
		break;
	}
}

// Checks if the click coordinates are inside the push wall button
bool Game::clickedPushW(Sint32 _mouseX, Sint32 _mouseY)
{
	if (_mouseX >= NSB_BT_X && _mouseX <= NSB_BT_X + 32)
	{
		if (_mouseY >= NSB_BT_Y && _mouseY <= NSB_BT_Y + 32)
		{
			return true;
		}
		return false;
	}
	return false;
}

// Updates game logic
void Game::update()
{
	// Push the wall each interval
	if (m_timer->getTicks() > (Uint32)PSH_INTV)
	{
		m_timer->stop();
		m_wall->pushWallLeft();
		m_timer->start();
	}
	// Loosing condition
	if (m_wall->getWall().wallMx[NROW-1][0] != 0)
	{
		cout << "You lost!" << endl;
		m_timer->stop();
		m_isRunning = false;
	}
	// Different stage every x score
	if (m_currScore > (STG_PTS * m_currStage))
	{
		m_currStage++;
		m_wall->initWall();
	}
}

// Updates game graphics
void Game::render()
{
	SDL_RenderClear(m_rend->getRenderer());
	
	// Renders wall and grid, timer, score, and curr. stage
	m_rend->renderGame(&m_wall->getWall());
	m_rend->renderTimer(m_timer->getTicks());
	m_rend->renderScore(m_currScore);
	m_rend->renderStage(m_currStage);

	SDL_RenderPresent(m_rend->getRenderer());
}

void Game::clean()
{
	m_rend->~RenderMng();
	m_wall->~Wall();
	m_timer->~Timer();

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	cout << "Game closed" << endl;
}


