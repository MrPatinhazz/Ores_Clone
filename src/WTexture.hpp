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
	void render(int x, int y);
	void render(SDL_Rect dstRect);

	// Getter & setter for tex dimensions and location
	int Width() { return texW; };
	void setWidth(int w) { texW = w; };

	int Height() { return texH; };
	void setHeight(int h) { texH = h; };

	int Xcoord() { return texX; };
	void setX(int x) { texX = x; };

	int Ycoord() { return texY; };
	void setY(int y) { texY = y; };
	
	//Sets renderer
	void setRend(SDL_Renderer* rend) { tRend = rend; };

	// Loads texture from sys path
	bool loadFromFile(string path);

	// Load texture from inputed text
	bool loadFromText(string text, SDL_Color textColor, TTF_Font* font);

private:
	// Hardware texture
	SDL_Texture* tTex;

	// Used renderer
	SDL_Renderer* tRend;

	// Texture dimensions width and height and location X & Y
	int texW, texH, texX, texY;
};