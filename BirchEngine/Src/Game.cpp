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

std::vector<ColliderComponent*> Game::colliders;

bool Game::isRunning = false;

auto& player(manager.addEntity());
auto& enemy(manager.addEntity());
auto& wall = manager.addEntity();

const char* mapfile = "assets/terrain_ss.png";

enum groupLabels : std::size_t
{
	GROUP_MAP,
	GROUP_PLAYERS,
	GROUP_ENEMIES,
	GROUP_COLLIDERS
};

auto& tiles(manager.getGroup(GROUP_MAP));
auto& players(manager.getGroup(GROUP_PLAYERS));
auto& enemies(manager.getGroup(GROUP_ENEMIES));
auto& colliders(manager.getGroup(GROUP_COLLIDERS));

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

	Map::LoadMap("assets/map.map", 25, 20);

	player.addComponent<TransformComponent>(400.0f, 320.0f,32,32,2);
	player.addComponent<SpriteComponent>("assets/player_anims.png", true);
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	player.addGroup(GROUP_PLAYERS);

	enemy.addComponent<TransformComponent>(50,50);
	enemy.addComponent<SpriteComponent>("assets/bar2.png");
	enemy.addGroup(GROUP_PLAYERS);

	wall.addComponent<TransformComponent>(300.0f, 300.0f, 300, 20, 1);
	wall.addComponent<SpriteComponent>("assets/dirt.png");
	wall.addComponent<ColliderComponent>("wall");
	wall.addGroup(GROUP_COLLIDERS);

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

	Vector2D pVel = player.getComponent<TransformComponent>().velocity;
	int pSpeed = player.getComponent<TransformComponent>().speed;

	for (auto t : tiles)
	{
		t->getComponent<TileComponent>().destRect.x += -(pVel.x * pSpeed);
		t->getComponent<TileComponent>().destRect.y += -(pVel.y * pSpeed);

	}

	enemy.getComponent<TransformComponent>().position *= Vector2D(0.0, 1.01);


	for (auto cc : colliders)
	{
		Collision::AABB(player.getComponent<ColliderComponent>(), *cc);
	}


	std::cout << cnt << std::endl;
}

void Game::render()
{
	SDL_RenderClear(renderer);

	// manager.draw();
	
	for (auto& t : tiles)
	{
		t->draw();
	}


	for (auto& p : players)
	{
		p->draw();
	}


	for (auto& e : enemies)
	{
		e->draw();
	}

	for (auto& c : colliders)
	{
		c->draw();
	}

	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

void Game::AddTile(int srcX, int srcY, int xpos, int ypos)
{

	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(srcX,srcY, xpos, ypos, mapfile);
	tile.addGroup(GROUP_MAP);
}
