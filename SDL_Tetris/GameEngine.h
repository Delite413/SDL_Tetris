#pragma once

#include <SDL/SDL.h>
#include <deque>
#include <memory>
#include <random>

#include "Board.h"
#include "Tetromino.h"
#include "UserInterface.h"

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
	UserInterface* _userInterface;

	std::deque<std::shared_ptr<Tetromino>> _bagOfTetrominos;

	void generateTetrominos();
};

