#pragma once

#include <SDL/SDL.h>
#include <deque>
#include <random>

#include "Board.h"
#include "Tetromino.h"
#include "T_Block.h"

class GameEngine
{
public:
	GameEngine();
	~GameEngine();

	static const int BLOCK_SIZE = 20;

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

	Board* _gameBoard;
	Tetromino* _tetromino;

	std::deque<Tetromino*> _bagOfTetrominos;

	void generateTetrominos();
};

