#include "L_Block.h"


L_Block::L_Block(SDL_Renderer* _renderer, Board* _gameBoard) : _renderer(_renderer), _gameBoard(_gameBoard)
{
	// Set Initial Starting Positions
	_startingXPos = 230;
	_startingYPos = 110;
	_x = _startingXPos;
	_y = _startingYPos;
	_blockMapWidth = 4;
	_blockMapHeight = 4;
	/*
	L_Block Map
	      [1]
	[2][3][4]
	*/
	blockMap[1][3] = 1;
	blockMap[2][1] = 1;
	blockMap[2][2] = 2;
	blockMap[2][3] = 1;
}


L_Block::~L_Block()
{
}

void L_Block::render()
{
	for (int i = 0; i < _blockMapHeight; i++) {
		for (int j = 0; j < _blockMapWidth; j++) {
			if (blockMap[j][i] != 0) {

				// Draw Individual Blocks
				SDL_Rect lBlock_Block;
				lBlock_Block.h = BLOCK_SIZE;
				lBlock_Block.w = BLOCK_SIZE;
				lBlock_Block.x = _x + (i * BLOCK_SIZE);
				lBlock_Block.y = _y + (j * BLOCK_SIZE);

				// Render Purple T
				SDL_SetRenderDrawColor(_renderer, 255, 102, 0, 255);
				SDL_RenderFillRect(_renderer, &lBlock_Block);
			}
		}
	}
}
