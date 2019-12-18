#pragma once

// Texture class - holds information and methods about each texture in game. Can be further
// developed to include color keying , alpha bleding, animations etc...
// setLoc() exists outside texture constructor due to future plans to add animation.

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

class WTexture
{
public:
	// Inits texture
	WTexture();
	WTexture(SDL_Renderer* rend);

	// Destroys texture
	void free();
	~WTexture() { free(); };

	// Renders texture at the current location, with current size
	void render();

	//Set blending mode
	void setBlendMode(SDL_BlendMode b_mode)
	{
		SDL_SetTextureBlendMode(m_tex, b_mode);
	};

	//Set texture alpha (transparency)
	void setAlpha(Uint8 a)
	{
		SDL_SetTextureAlphaMod(m_tex, a);
	}

	// Getter & setter for tex dimensions and location
	unsigned int Width() { return m_tex_w; };
	unsigned int Height() { return m_tex_h; };
	void setSize(unsigned int _w, unsigned int _h)
	{
		m_tex_w = _w;
		m_tex_h = _h;
	}

	unsigned int Xcoord() { return m_tex_x; };
	unsigned int Ycoord() { return m_tex_y; };
	void setLoc(unsigned int _x , unsigned int _y)
	{
		m_tex_x = _x;
		m_tex_y = _y;
	}

	
	//Sets renderer
	void setRend(SDL_Renderer* _rend) { m_rend = _rend; };

	// Loads texture from sys path
	bool loadFromFile(string _path);

	// Load texture from inputed text
	bool loadFromText(string _text, SDL_Color _textColor, TTF_Font* _font);

private:
	// Hardware texture
	SDL_Texture* m_tex;

	// Used renderer
	SDL_Renderer* m_rend;

	// Texture dimensions width and height and location X & Y
	unsigned int m_tex_w, m_tex_h, m_tex_x, m_tex_y;
};