#pragma once

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
	~WTexture();
	void free();

	// Renders texture at location with img size or param size
	void render(unsigned int x, unsigned int y);
	void render(SDL_Rect m_dst_rect);

	//Set blending
	void setBlendMode(SDL_BlendMode b_mode);

	//Set alpha modulation
	void setAlpha(Uint8 a);

	// Getter & setter for tex dimensions and location
	unsigned int Width() { return m_tex_w; };
	void setWidth(unsigned int _w) { m_tex_w = _w; };

	unsigned int Height() { return m_tex_h; };
	void setHeight(unsigned _h) { m_tex_h = _h; };

	unsigned int Xcoord() { return m_tex_x; };
	void setX(unsigned _x) { m_tex_x = _x; };

	unsigned int Ycoord() { return m_tex_y; };
	void setY(unsigned _y) { m_tex_y = _y; };
	
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
	int m_tex_w, m_tex_h, m_tex_x, m_tex_y;
};