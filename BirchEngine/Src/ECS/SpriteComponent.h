#pragma once

#include "Components.h"
#include "SDL.h"

class SpriteComponent : public Component
{
private:
	PositionComponent* position;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

public:
	SpriteComponent() = default;
	SpriteComponent(const char* path)
	{
		texture = TextureManager::LoadTexture(path);
	}

	void init() override
	{
		position = &entity->getComponent<PositionComponent>();
		
		srcRect.x = srcRect.y = 0;
		srcRect.w = 16; // in the future, this has to be changed based on the particular asset/png size.
		srcRect.h = 64;
		destRect.w = srcRect.w * 2;
		destRect.h = srcRect.h * 2;

	}

	void update() override
	{
		destRect.x = position->x();
		destRect.y = position->y();
	}

	void draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect);
	}

};
