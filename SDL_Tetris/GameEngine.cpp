#include "GameEngine.h"
#include <iostream>


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

	//Create GameBoard Instance
	_gameBoard = new Board(_renderer);
}

void GameEngine::gameLoop()
{
		SDL_SetRenderTarget(_renderer, NULL);
		SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 0);
		SDL_RenderClear(_renderer);

		generateTetrominos();
		handleInput();
		update();
		render();
		testBlock();

		SDL_RenderPresent(_renderer);
		SDL_Delay(300);
}

void GameEngine::checkValidMove()
{
	if ((*_bagOfTetrominos.front()).checkCollision() == false) {
		(*_bagOfTetrominos.front()).moveBlock();
	}
	else {
		(*_bagOfTetrominos.front()).placeBricks();
		_bagOfTetrominos.pop_front();
	}
}

void GameEngine::generateTetrominos()
{
	if (_bagOfTetrominos.size() <= 1) {
		//Create a Random Number between 1 and 7 ( 1 for Each Shape )
		std::random_device rd;
		std::default_random_engine generator(rd());
		std::uniform_int_distribution<int> distribution(1, 1);


		for (int i = 0; i < 3; i++) {
			int generatedNumber = distribution(generator);

			//Add the Random Tetromino to the Vector
			//std::cout << "Generated Number: " << generatedNumber << std::endl;
			switch (generatedNumber) {
			case 1:
				_bagOfTetrominos.push_back(new T_Block(_renderer, _gameBoard));
				break;
			default:
				break;
			}
		}
	}
}

void GameEngine::handleInput()
{
	SDL_Event evnt;

	while (SDL_PollEvent(&evnt)) {
		switch (evnt.type) {
		case SDL_QUIT:
			inGame = false;
			break;
		case SDL_KEYDOWN:
			if (evnt.key.keysym.sym == SDLK_RIGHT) {
				(*_bagOfTetrominos.front()).setX((*_bagOfTetrominos.front()).getX() + BLOCK_SIZE);
			}
			if (evnt.key.keysym.sym == SDLK_LEFT) {
				(*_bagOfTetrominos.front()).setX((*_bagOfTetrominos.front()).getX() - BLOCK_SIZE);
			}
			if (evnt.key.keysym.sym == SDLK_UP) {
				(*_bagOfTetrominos.front()).rotateClockwise();
			}
			break;
		default:
			break;
		}
	}
}

void GameEngine::update()
{
	_gameBoard->update();
	checkValidMove();

}

void GameEngine::render()
{
	// Draw Game Board
	_gameBoard->render();

	// Draw Active Tetromino
	(*_bagOfTetrominos.front()).render();

}

void GameEngine::close()
{
	// Destroy All The Things!
	delete _gameBoard;
	_gameBoard = nullptr;
	SDL_DestroyRenderer(_renderer);
	_renderer = nullptr;
	SDL_DestroyWindow(_window);
	_window = nullptr;
	SDL_Quit();
}

void GameEngine::testBlock()
{
	// Test Outputs

		// BlockMap Values
		//std::cout << (*_bagOfTetrominos.front()).blockMap[0][1] << std::endl;

		// Starting Position Check
		std::cout << "(" << (*_bagOfTetrominos.front()).getX() << ", " << (*_bagOfTetrominos.front()).getY() << ")" << std::endl;
}