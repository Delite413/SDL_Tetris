#include "T_Block.h"
#include <iostream>


T_Block::T_Block(SDL_Renderer* _renderer) : _renderer(_renderer)
{
	_xPos = 214;
	_yPos = 150;
	_tBlock[0][1] = 1;
	_tBlock[1][1] = 1;
	_tBlock[1][2] = 1;
	_tBlock[2][1] = 1;

	// Create Block Texture
	defineBlock();
}

T_Block::~T_Block()
{
}

void T_Block::render()
{
	for (int i = 1; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (_tBlock[j][i] == 1) {

				targetRect.h = Tetromino::_blockHeight;
				targetRect.w = Tetromino::_blockWidth;
				targetRect.x = _xPos + (i * Tetromino::_blockSize);
				targetRect.y = _yPos + (j * Tetromino::_blockSize);

				SDL_SetRenderDrawColor(_renderer, 255, 0, 0, 255);
				SDL_RenderFillRect(_renderer, &targetRect);

			}
		}
	}
}

void T_Block::defineBlock()
{

	tetrominoTexture = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, Tetromino::_blockWidth, Tetromino::_blockHeight);
	SDL_SetTextureBlendMode(tetrominoTexture, SDL_BLENDMODE_ADD);

	SDL_Rect tetromino;

	tetromino.x = 0;
	tetromino.y = 0;
	tetromino.w = Tetromino::_blockWidth;
	tetromino.h = Tetromino::_blockHeight;

	_tetromino = tetromino;

	SDL_SetRenderTarget(_renderer, tetrominoTexture);
	SDL_SetRenderDrawColor(_renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(_renderer, &tetromino);
}

void T_Block::update()
{
	render();
}
