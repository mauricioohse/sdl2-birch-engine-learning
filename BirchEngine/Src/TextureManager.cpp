#include "TextureManager.h"


SDL_Texture* TextureManager::LoadTexture(const char* file)
{
	SDL_Surface* tempSurface = IMG_Load(file);
	if (tempSurface == NULL)
	{
		printf("Unable to load image! SDL_image Error: %s\n", IMG_GetError());
	}

	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
	SDL_FreeSurface(tempSurface);
	return tex;
}

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest)
{
	SDL_RenderCopy(Game::renderer, tex, &src, &dest);
}
