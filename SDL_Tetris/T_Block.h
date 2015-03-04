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
	void defineBlock();
	void placeBrick();	
	void render();
	void rotate();
	void update();
	bool validLeftLateralMovement();
	bool validRightLateralMovement();

	SDL_Rect targetRect;

	int tBlock[3][3];

private:

	Board* _gameBoard;
	SDL_Renderer* _renderer;
	SDL_Rect _tetromino;	
};

