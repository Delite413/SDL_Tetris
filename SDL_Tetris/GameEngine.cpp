#include "GameEngine.h"
#include "I_Block.h"
#include "J_Block.h"
#include "L_Block.h"
#include "O_Block.h"
#include "S_Block.h"
#include "T_Block.h"
#include "Z_Block.h"

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

	// SDL_TTF
	TTF_Init();

	// Create SDL Window
	_window = SDL_CreateWindow("SDL Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);

	// Create SDL Renderer
	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);

	// Create GameBoard Instance
	_gameBoard = new Board(_renderer);

	// Create User Interface Instance
	_userInterface = new UserInterface(_renderer);
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

	SDL_RenderPresent(_renderer);
	SDL_Delay(200);
}

void GameEngine::generateTetrominos()
{
	if (_bagOfTetrominos.size() <= 1) {
		//Create a Random Number between 1 and 7 ( 1 for Each Shape )
		std::random_device rd;
		std::default_random_engine generator(rd());
		std::uniform_int_distribution<int> distribution(1, 7);


		for (int i = 0; i < 10; ++i) {
			int generatedNumber = distribution(generator);

			//Add the Random Tetromino to the Vector
			//std::cout << "Generated Number: " << generatedNumber << std::endl;
			switch (generatedNumber) {
			case 1:
				_bagOfTetrominos.emplace_back(std::make_unique<T_Block>(_renderer, _gameBoard));
				break;
			case 2:
				_bagOfTetrominos.emplace_back(std::make_unique<J_Block>(_renderer, _gameBoard));
				break;
			case 3:
				_bagOfTetrominos.emplace_back(std::make_unique<S_Block>(_renderer, _gameBoard));
				break;
			case 4:
				_bagOfTetrominos.emplace_back(std::make_unique<Z_Block>(_renderer, _gameBoard));
				break;
			case 5:
				_bagOfTetrominos.emplace_back(std::make_unique<L_Block>(_renderer, _gameBoard));
				break;
			case 6:
				_bagOfTetrominos.emplace_back(std::make_unique<I_Block>(_renderer, _gameBoard));
				break;
			case 7:
				_bagOfTetrominos.emplace_back(std::make_unique<O_Block>(_renderer, _gameBoard));
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
				if (_bagOfTetrominos.front()->checkCollision(_bagOfTetrominos.front()->getX() + BLOCK_SIZE, _bagOfTetrominos.front()->getY(), _gameBoard)) {
					// Do Nothing
				}
				else {
					_bagOfTetrominos.front()->setX(_bagOfTetrominos.front()->getX() + BLOCK_SIZE);
				}
			}
			if (evnt.key.keysym.sym == SDLK_LEFT) {
				if (_bagOfTetrominos.front()->checkCollision(_bagOfTetrominos.front()->getX() - BLOCK_SIZE, _bagOfTetrominos.front()->getY(), _gameBoard)) {
					 // Do Nothing
				}
				else {
					_bagOfTetrominos.front()->setX(_bagOfTetrominos.front()->getX() - BLOCK_SIZE);
				}
			}
			if (evnt.key.keysym.sym == SDLK_UP) {
				_bagOfTetrominos.front()->rotateClockwise(_gameBoard);
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
	if (_bagOfTetrominos.front()->checkCollision(_bagOfTetrominos.front()->getX(), _bagOfTetrominos.front()->getY() + BLOCK_SIZE, _gameBoard)) {
		_bagOfTetrominos.front()->placeBricks(_gameBoard, typeid((*_bagOfTetrominos.front())));
		_bagOfTetrominos.pop_front();
	}
	else {
		_bagOfTetrominos.front()->moveBlock();
	}
	_gameBoard->checkForLines();
}

void GameEngine::render()
{
	// Draw Game Board
	_gameBoard->render();

	// Draw Active Tetromino
	_bagOfTetrominos.front()->render();

	// Draw UI Elements
	_userInterface->render();

}

void GameEngine::close()
{
	// Destroy All The Things!
	delete _userInterface;
	_userInterface = nullptr;
	delete _gameBoard;
	_gameBoard = nullptr;
	SDL_DestroyRenderer(_renderer);
	_renderer = nullptr;
	SDL_DestroyWindow(_window);
	_window = nullptr;
	TTF_Quit();
	SDL_Quit();
}