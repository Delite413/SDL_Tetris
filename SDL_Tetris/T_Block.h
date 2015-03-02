#pragma once

#include <SDL/SDL.h>

#include "Tetromino.h"

class T_Block :
	public Tetromino
{
public:
	T_Block(SDL_Renderer* _renderer);
	~T_Block();

	SDL_Texture* tetrominoTexture;

	void render();
	void defineBlock();
	void update();

	SDL_Rect targetRect;

private:

	unsigned int _blockSize;
	int _tBlock[3][3];

	SDL_Renderer* _renderer;
	SDL_Rect _tetromino;

	
};

