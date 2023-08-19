#include "Game.h"
#include "TextureManager.h"
#include "map.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"

Map* map;

SDL_Renderer* Game::renderer = nullptr;

Manager manager;
SDL_Event Game::event;
auto& player(manager.addEntity());
auto& enemy(manager.addEntity());
auto& wall = manager.addEntity();

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

	player.addComponent<TransformComponent>(2);
	player.addComponent<SpriteComponent>("assets/bar.png");
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");

	enemy.addComponent<TransformComponent>(50,50);
	enemy.addComponent<SpriteComponent>("assets/bar2.png");

	wall.addComponent<TransformComponent>(300.0f, 300.0f, 300, 20, 1);
	wall.addComponent<SpriteComponent>("assets/dirt.png");
	wall.addComponent<ColliderComponent>("wall");
}

void Game::handleEvents()
{

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

void Game::update() // currently doing things here to test, but the scripts will change places
{
	cnt++;

	manager.refresh();
	manager.update();

	enemy.getComponent<TransformComponent>().position *= Vector2D(0.0, 1.01);


	if (player.getComponent<TransformComponent>().position.x > 100)
	{
		player.getComponent<SpriteComponent>().SetTex("assets/bar2.png");
	}


	if (Collision::AABB(player.getComponent<ColliderComponent>().collider, 
						wall.getComponent<ColliderComponent>().collider))
	{
		player.getComponent<TransformComponent>().scale = 1;
		player.getComponent<TransformComponent>().velocity * -1;
		std::cout << "collided!" << std::endl;
	}


	std::cout << cnt << std::endl;
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