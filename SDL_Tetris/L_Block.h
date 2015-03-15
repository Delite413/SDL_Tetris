#pragma once

#include "Board.h"
#include "Tetromino.h"

#include <SDL/SDL.h>

class L_Block :
	public Tetromino
{
public:
	L_Block(SDL_Renderer* _renderer, Board* _gameBoard, int _startingXPos, int _startingYPos);
	~L_Block();

	void render();

private:
	Board* _gameBoard;
	SDL_Renderer* _renderer;
};

