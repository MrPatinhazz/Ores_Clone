#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>

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

	// Getter & setter for tex dimensions
	int Width() { return texW; };
	void setWidth(int w) { texW = w; };

	int Height() { return texH; };
	void setHeight(int h) { texH = h; };
	
	//Sets renderer
	void setRend(SDL_Renderer* rend) { tRend = rend; };

	// Loads texture from sys path
	bool LoadFromFile(string path);

private:
	// Hardware texture
	SDL_Texture* tTex;

	// Used renderer
	SDL_Renderer* tRend;

	// Texture dimensions width and height
	int texW;
	int texH;

};