#include "T_Block.h"

#include <iostream>
T_Block::T_Block(SDL_Renderer* _renderer, Board* _gameBoard) : _renderer(_renderer), _gameBoard(_gameBoard)
{
	// Set Initial Starting Positions
	_startingXPos = 230;
	_startingYPos = 150;
	_x = _startingXPos;
	_y = _startingYPos;
	_blockMapWidth = 4;
	_blockMapHeight = 4;
	/* 
	T-Block Map
	    [0]
	 [1][2][3]
	*/
	blockMap[1][2] = 1;
	blockMap[2][1] = 1;
	blockMap[2][2] = 2;
	blockMap[2][3] = 1;
}

T_Block::~T_Block()
{

}

void T_Block::render()
{
	for (int i = 0; i < _blockMapHeight; i++) {
		for (int j = 0; j < _blockMapWidth; j++) {
			if (blockMap[j][i] != 0) {

				// Draw Individual Blocks
				SDL_Rect tBlock_Block;
				tBlock_Block.h = BLOCK_SIZE;
				tBlock_Block.w = BLOCK_SIZE;
				tBlock_Block.x = _x + ( i * BLOCK_SIZE );
				tBlock_Block.y = _y + ( j * BLOCK_SIZE );
				
				// Render Purple T
				SDL_SetRenderDrawColor(_renderer, 255, 0, 255, 255);
				SDL_RenderFillRect(_renderer, &tBlock_Block);
			}
		}
	}
}

