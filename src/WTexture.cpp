#include "WTexture.hpp"

WTexture::WTexture()
{
	tTex = NULL;
	texW = 0, texH = 0, texX = 0, texY = 0;
	tRend = NULL;
}

WTexture::WTexture(SDL_Renderer* rend)
{
	tTex = NULL;
	texW = 0, texH = 0, texX = 0, texY = 0;
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
		texW = 0, texH = 0, texX = 0, texY = 0;
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

// Loads texture from system path
bool WTexture::loadFromFile(string path)
{
	// Erases previous texture
	free();

	// Load image from path
	SDL_Surface* tempSurface = IMG_Load(path.c_str());
	if (tempSurface == NULL)
	{
		cout << "Image loading error: " << IMG_GetError() << endl;
	}
	else
	{
		// Create texture from prev. generated surface
		tTex = SDL_CreateTextureFromSurface(tRend, tempSurface);

		if (tTex == NULL)
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

	// Set obj. texture and return sucess state
	return tTex != NULL;
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
		tTex = SDL_CreateTextureFromSurface(tRend, textSurface);
		if (tTex == NULL)
		{
			cout << "Error creating text from surface: " << SDL_GetError() << endl;
		}
		else
		{
			texW = textSurface->w;
			texH = textSurface->h;
		}

		SDL_FreeSurface(textSurface);
	}

	//Return sucess if created
	return tTex != NULL;
}
