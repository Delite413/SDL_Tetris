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

		SDL_RenderPresent(_renderer);
		SDL_Delay(300);
}

void GameEngine::generateTetrominos()
{
	if (_bagOfTetrominos.size() <= 1) {
		//Create a Random Number between 1 and 7 ( 1 for Each Shape )
		std::random_device rd;
		std::default_random_engine generator(rd());
		std::uniform_int_distribution<int> distribution(1, 1);


		for (int i = 0; i < 5; i++) {
			int generatedNumber = distribution(generator);

			//Add the Random Tetromino to the Vector
			std::cout << "Generated Number: " << generatedNumber << std::endl;
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
				if ((*_bagOfTetrominos.front()).validRightLateralMovement()) {
					(*_bagOfTetrominos.front()).setX((*_bagOfTetrominos.front()).getX() + BLOCK_SIZE);
				}
			}
			if (evnt.key.keysym.sym == SDLK_LEFT) {
				if ((*_bagOfTetrominos.front()).validLeftLateralMovement()) {
					(*_bagOfTetrominos.front()).setX((*_bagOfTetrominos.front()).getX() - BLOCK_SIZE);
				}
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
	// Test Code
	convertCoord();
	//
	moveBrick();
}

void GameEngine::render()
{
	// Draw Game Board
	_gameBoard->render();

	//Draw Current Tetromino
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

bool GameEngine::checkValidMove()
{
		// Invalid Move Checks
	// Check if hits bottom of bucket
	if (_convertedY == 17) {
		(*_bagOfTetrominos.front()).placeBrick();
		_bagOfTetrominos.pop_front();
		return false;
	}

	// Checks for Collisions
	if ((*_bagOfTetrominos.front()).checkCollision()) {
		(*_bagOfTetrominos.front()).placeBrick();
		_bagOfTetrominos.pop_front();
		return false;
	}

	return true;
}

void GameEngine::convertCoord()
{
	// Convert X Coordinate
	_convertedX = ((*_bagOfTetrominos.front()).getX() - 150) / 16;

	// Converted Y Coordinate
	_convertedY = ((*_bagOfTetrominos.front()).getY() - 150) / 16;
}

void GameEngine::moveBrick()
{
	if (checkValidMove()) {
		//Move Brick Down the Screen
		(*_bagOfTetrominos.front()).setY((*_bagOfTetrominos.front()).getY() + BLOCK_SIZE);
	}
}
