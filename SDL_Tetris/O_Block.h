#pragma once

#include "Board.h"
#include "Tetromino.h"

#include <SDL/SDL.h>

class O_Block :
	public Tetromino
{
public:
	O_Block(SDL_Renderer* _renderer, Board* _gameBoard, int _startingXPos, int _startingYPos);
	~O_Block();

	void render();

private:
	
	Board* _gameBoard;
	SDL_Renderer* _renderer;
};

