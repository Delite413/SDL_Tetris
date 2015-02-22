#pragma once

#include <SDL/SDL.h>

class GameEngine
{
public:
	GameEngine();
	~GameEngine();

	bool inGame;

	void run();
	void init();
	void gameLoop();
	void handleInput();
	void update();
	void render();
	void close();

private:
	SDL_Window* _window;
	SDL_Renderer* _renderer;
	
};

