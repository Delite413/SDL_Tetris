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

	SDL_Texture* tetrominoTexture;

	bool checkCollision();
	bool validLeftLateralMovement();
	bool validRightLateralMovement();
	void render();
	void defineBlock();
	void placeBrick();
	void update();

	SDL_Rect targetRect;

	int tBlock[3][3];

private:

	Board* _gameBoard;
	SDL_Renderer* _renderer;
	SDL_Rect _tetromino;

	
};

