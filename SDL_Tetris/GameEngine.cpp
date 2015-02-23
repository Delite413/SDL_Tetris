#include "GameEngine.h"


GameEngine::GameEngine() : inGame(true), _window(nullptr), _renderer(nullptr)
{
}

GameEngine::~GameEngine()
{
}

void GameEngine::run()
{
	init();

	while (inGame) {
		gameLoop();
	}
	
	close();
}

void GameEngine::init()
{
	// Initialize SDL
	SDL_Init(SDL_INIT_EVERYTHING);

	// Create SDL Window
	_window = SDL_CreateWindow("SDL Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);

	// Create SDL Renderer
	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);


}

void GameEngine::gameLoop()
{
	handleInput();
	update();
	render();
}

void GameEngine::handleInput()
{
	SDL_Event evnt;

	while (SDL_PollEvent(&evnt)) {
		if (evnt.type == SDL_QUIT)
			inGame = false;
	}
}

void GameEngine::update()
{

}

void GameEngine::render()
{
	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
	SDL_RenderClear(_renderer);


	SDL_RenderPresent(_renderer);
}

void GameEngine::close()
{
	// Destroy All The Things!
	SDL_DestroyRenderer(_renderer);
	_renderer = nullptr;
	SDL_DestroyWindow(_window);
	_window = nullptr;
	SDL_Quit();
}