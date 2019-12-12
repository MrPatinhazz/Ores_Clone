#include "WTexture.hpp"

WTexture::WTexture()
{
	m_tex = NULL;
	m_tex_w = 0, m_tex_h = 0, m_tex_x = 0, m_tex_y = 0;
	m_rend = NULL;
}

WTexture::WTexture(SDL_Renderer* _rend)
{
	m_tex = NULL;
	m_tex_w = 0, m_tex_h = 0, m_tex_x = 0, m_tex_y = 0;
	m_rend = _rend;
}

WTexture::~WTexture()
{
	free();
}

void WTexture::free()
{
	//Free texture if it exists
	if (m_tex != NULL)
	{
		SDL_DestroyTexture(m_tex);
		m_tex = NULL;
		m_tex_w = 0, m_tex_h = 0, m_tex_x = 0, m_tex_y = 0;
	}
}

void WTexture::render(unsigned int _x, unsigned int _y)
{
	//	Set rendering destination quad
	SDL_Rect renderQuad = { _x, _y, m_tex_w, m_tex_h};
	SDL_RenderCopy(m_rend, m_tex, NULL, &renderQuad);
}

void WTexture::render(SDL_Rect _m_dst_rect)
{
	SDL_RenderCopy(m_rend, m_tex, NULL, &_m_dst_rect);
}

// Loads texture from system path
bool WTexture::loadFromFile(string _path)
{
	// Erases previous texture
	free();

	// Load image from path
	SDL_Surface* tempSurface = IMG_Load(_path.c_str());
	if (tempSurface == NULL)
	{
		cout << "Image loading error: " << IMG_GetError() << endl;
	}
	else
	{
		// Create texture from prev. generated surface
		m_tex = SDL_CreateTextureFromSurface(m_rend, tempSurface);

		if (m_tex == NULL)
		{
			cout << "Texture creation error: " << SDL_GetError();
		}
		else
		{
			// Get dimensions
			m_tex_w = tempSurface->w;
			m_tex_h = tempSurface->h;
		}

		SDL_FreeSurface(tempSurface);
	}

	// Set obj. texture and return sucess state
	return m_tex != NULL;
}

// Loads texture from written text with a given font
bool WTexture::loadFromText(string text, SDL_Color textColor, TTF_Font* font)
{
	// Erases previous texture
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
	if (textSurface == NULL)
	{
		cout << "Error creating text surface :" << TTF_GetError() << endl;
	}
	else
	{
		//Create texture from surface
		m_tex = SDL_CreateTextureFromSurface(m_rend, textSurface);
		if (m_tex == NULL)
		{
			cout << "Error creating text from surface: " << SDL_GetError() << endl;
		}
		else
		{
			m_tex_w = textSurface->w;
			m_tex_h = textSurface->h;
		}

		SDL_FreeSurface(textSurface);
	}

	//Return sucess if created
	return m_tex != NULL;
}
