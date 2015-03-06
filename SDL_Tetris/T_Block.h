#pragma once

#include <SDL/SDL.h>

#include "Board.h"
#include "Tetromino.h"

class T_Block :
	public Tetromino
{
public:
	T_Block(SDL_Renderer* _renderer, Board* _gameBoard);
	~T_Block();

	bool     checkCollision();
	Vector2D getPivotCoords() { return _pivotCoords; }
	void     placeBricks();
	void     render();

private:
	Board* _gameBoard;
	SDL_Renderer* _renderer;
	Vector2D _pivotCoords;

};

