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

	bool     checkCollision(int xPos, int yPos);
	Vector2D checkRotationCollision(int xPos, int yPos);
	void     placeBricks();
	void     render();

private:
	Board* _gameBoard;
	SDL_Renderer* _renderer;

};

