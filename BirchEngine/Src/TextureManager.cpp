#include "TextureManager.h"


SDL_Texture* TextureManager::LoadTexture(const char* file, SDL_Renderer* ren)
{
	SDL_Surface* tempSurface = IMG_Load(file);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, tempSurface);
	SDL_FreeSurface(tempSurface);
	
	return tex;
}
