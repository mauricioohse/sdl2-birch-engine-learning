#pragma once

#include "Components.h"
#include "SDL.h"
#include "../TextureManager.h"

class SpriteComponent : public Component
{
private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

	bool animated = false;
	int frames = 0;
	int speed = 100;

public:
	SpriteComponent() = default;
	SpriteComponent(const char* path)
	{
		SetTex(path);
	}

	SpriteComponent(const char* path, int nFrames, int mSpeed)
	{
		animated = true;
		frames = nFrames;
		speed = mSpeed;
		SetTex(path);
	}

	~SpriteComponent()
	{
	SDL_DestroyTexture(texture);
	}

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		
		srcRect.x = srcRect.y = 0;
		srcRect.w = transform->width; // in the future, this has to be changed based on the particular asset/png size.
		srcRect.h = transform->height;
		destRect.w = srcRect.w * 2;
		destRect.h = srcRect.h * 2;

	}

	void update() override
	{
		if (animated)
		{
			srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
		}

		destRect.x = static_cast<int>(transform->position.x);
		destRect.y = static_cast<int>(transform->position.y);
		destRect.w = transform->width * transform->scale;
		destRect.h = transform->height * transform->scale;
	}

	void draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect);
	}

	void SetTex(const char* path) 
	{
		texture = TextureManager::LoadTexture(path);
	}

};
