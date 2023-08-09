#include "Game.h"
#include "TextureManager.h"
#include "map.h"
#include "ECS/Components.h"

Map* map;

SDL_Renderer* Game::renderer = nullptr;

Manager manager;
auto& player(manager.addEntity());
auto& enemy(manager.addEntity());

Game::Game()
{}

Game::~Game()
{}

void Game::init(const char* title, int width, int height, bool fullscreen)
{
	int flags = 0;
	
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}

		isRunning = true;
	}

	map = new Map();

	// ecs implementation

	player.addComponent<PositionComponent>();
	player.addComponent<SpriteComponent>("assets/bar.png");

	player.addComponent<PositionComponent>(50,50);
	player.addComponent<SpriteComponent>("assets/bar2.png");
}

void Game::handleEvents()
{
	SDL_Event event;

	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT :
		isRunning = false;
		break;
	default:
		break;
	}
}

void Game::update()
{
	cnt++;

	manager.refresh();
	manager.update();

	//std::cout << cnt << std::endl;
}

void Game::render()
{
	SDL_RenderClear(renderer);
	map->DrawMap();

	manager.draw();
	
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}