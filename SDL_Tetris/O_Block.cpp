#include "O_Block.h"


O_Block::O_Block(SDL_Renderer* _renderer, Board* _gameBoard) : _renderer(_renderer), _gameBoard(_gameBoard)
{
	// Set Initial Starting Positions
	_startingXPos = 230;
	_startingYPos = 110;
	_x = _startingXPos;
	_y = _startingYPos;
	_blockMapWidth = 5;
	_blockMapHeight = 5;
	/*
	L_Block Map
	[1][2]
	[3][4]
	*/
	blockMap[1][2] = 1;
	blockMap[1][3] = 1;
	blockMap[2][2] = 2;
	blockMap[2][3] = 1;
}


O_Block::~O_Block()
{
}

void O_Block::render()
{
	for (int i = 0; i < _blockMapHeight; ++i) {
		for (int j = 0; j < _blockMapWidth; j++) {
			if (blockMap[j][i] != 0) {

				// Draw Individual Blocks
				SDL_Rect oBlock_Block;
				oBlock_Block.h = BLOCK_SIZE;
				oBlock_Block.w = BLOCK_SIZE;
				oBlock_Block.x = _x + (i * BLOCK_SIZE);
				oBlock_Block.y = _y + (j * BLOCK_SIZE);

				// Render Blue I
				SDL_SetRenderDrawColor(_renderer, 255, 204, 0, 255);
				SDL_RenderFillRect(_renderer, &oBlock_Block);
				SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
				SDL_RenderDrawRect(_renderer, &oBlock_Block);
			}
		}
	}
}
