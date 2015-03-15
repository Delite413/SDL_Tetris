#pragma once

#include "Board.h"
#include "Tetromino.h"

#include <SDL/SDL.h>
class S_Block :
	public Tetromino
{
public:
	S_Block(SDL_Renderer* _renderer, Board* _gameBoard, int _startingXPos, int _startingYPos);
	~S_Block();

	void render();

private:
	Board* _gameBoard;
	SDL_Renderer* _renderer;
};

