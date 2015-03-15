#pragma once

#include "Board.h"
#include "Tetromino.h"

#include <SDL/SDL.h>

class J_Block :
	public Tetromino
{
public:
	J_Block(SDL_Renderer* _renderer, Board* _gameBoard, int _startingXPos, int _startingYPos);
	~J_Block();

	void render();

private:
	Board* _gameBoard;
	SDL_Renderer* _renderer;
};

