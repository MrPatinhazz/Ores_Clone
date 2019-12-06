#include "WTexture.hpp"

WTexture::WTexture()
{
	tTex = NULL;
	texW = 0;
	texH = 0;
	tRend = NULL;
}

WTexture::WTexture(SDL_Renderer* rend)
{
	tTex = NULL;
	texW = 0;
	texH = 0;
	tRend = rend;
}

WTexture::~WTexture()
{
	free();
}

void WTexture::free()
{
	//Free texture if it exists
	if (tTex != NULL)
	{
		SDL_DestroyTexture(tTex);
		tTex = NULL;
		texW = 0;
		texH = 0;
	}
}

void WTexture::render(int x, int y)
{
	//	Set rendering destination quad
	SDL_Rect renderQuad = { x, y, texW, texH};
	SDL_RenderCopy(tRend, tTex, NULL, &renderQuad);
}

void WTexture::render(SDL_Rect dstRect)
{
	SDL_RenderCopy(tRend, tTex, NULL, &dstRect);
}

bool WTexture::LoadFromFile(string path)
{
	// Erases previous texture
	free();

	// Target texture
	SDL_Texture* tex = NULL;

	// Load image from path
	SDL_Surface* tempSurface = IMG_Load(path.c_str());
	if (tempSurface == NULL)
	{
		cout << "Image loading error: " << IMG_GetError() << endl;
	}
	else
	{
		tex = SDL_CreateTextureFromSurface(tRend, tempSurface);

		if (tex == NULL)
		{
			cout << "Texture creation error: " << SDL_GetError();
		}
		else
		{
			// Get dimensions
			texW = tempSurface->w;
			texH = tempSurface->h;
		}

		SDL_FreeSurface(tempSurface);
	}

	tTex = tex;
	return tTex != NULL;
}
