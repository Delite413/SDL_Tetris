#pragma once
#include <SDL/SDL.h>

#include "Board.h"
#include "Tetromino.h"

class Z_Block :
	public Tetromino
{
public:
	Z_Block(SDL_Renderer* _renderer, Board* _gameBoard, int _startingXPos, int _startingYPos);
	~Z_Block();

	void render();

private:

	Board* _gameBoard;
	SDL_Renderer* _renderer;
};

