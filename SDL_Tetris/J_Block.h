#pragma once

#include "Board.h"
#include "Tetromino.h"

#include <SDL/SDL.h>

class J_Block :
	public Tetromino
{
public:
	J_Block(SDL_Renderer* _renderer, Board* _gameBoard);
	~J_Block();

	void render();

private:
	Board* _gameBoard;
	SDL_Renderer* _renderer;
};

