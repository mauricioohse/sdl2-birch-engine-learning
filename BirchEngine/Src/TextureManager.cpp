#include "TextureManager.h"


SDL_Texture* TextureManager::LoadTexture(const char* file, SDL_Renderer* ren)
{
	SDL_Surface* tempSurface = IMG_Load(file);
	if (tempSurface == NULL)
	{
		printf("Unable to load image! SDL_image Error: %s\n", IMG_GetError());
	}

	SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, tempSurface);
	SDL_FreeSurface(tempSurface);
	
	return tex;
}
