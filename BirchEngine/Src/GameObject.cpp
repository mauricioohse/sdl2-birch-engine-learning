#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const char* textureSheet, SDL_Renderer* ren, int x, int y)
{
	xpos = x;
	ypos = y;

	renderer = ren;
	objTexture = TextureManager::LoadTexture(textureSheet, ren);
}

void GameObject::Update()
{
	xpos++;
	ypos++;

	srcRect.h = 64;
	srcRect.w = 16;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.h = srcRect.h * 2;
	destRect.w = srcRect.w * 2;

}

void GameObject::Render()
{
	SDL_RenderCopy(renderer, objTexture, &srcRect, & destRect);
}