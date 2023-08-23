#include "AssetManager.h"

AssetManager::AssetManager(Manager* man) : manager(man)
{}

AssetManager::~AssetManager()
{}

void AssetManager::AddTexture(std::string id, const char* path)
{
	textures.emplace(id, TextureManager::LoadTexture(path)); // LoadTexture loads the texture and returns the SDL_Texture pointer to be stored in textures
}

SDL_Texture* AssetManager::GetTexture(std::string id)
{
	return textures[id];
}
