#pragma once

#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
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
	void loadMedia();
	void update();
	void render();
	void close();

private:
	unsigned long _playerScore;
	unsigned int _linesDeleted;
	int _multiplier;
	unsigned int _level;
	unsigned long _runningTime;
	unsigned long _timeStart;
	unsigned long _timeEnd;
	unsigned long _waitTime;

	SDL_Window* _window;
	SDL_Renderer* _renderer;

	Board* _gameBoard;
	Mix_Music* _tetrisTheme;
	Tetromino* _tetromino;
	UserInterface* _userInterface;

	std::deque<std::shared_ptr<Tetromino>> _bagOfTetrominos;

	void generateTetrominos();
};

