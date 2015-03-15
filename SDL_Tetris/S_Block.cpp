#include "S_Block.h"


S_Block::S_Block(SDL_Renderer* _renderer, Board* _gameBoard, int _startingXPos, int _startingYPos) : _renderer(_renderer), _gameBoard(_gameBoard)
{
	// Set Initial Starting Positions
	_x = _startingXPos;
	_y = _startingYPos;
	_blockMapWidth = 4;
	_blockMapHeight = 4;
	/*
	S-Block Map
	   [1][2]
	[4][3]
	*/
	blockMap[1][2] = 1;
	blockMap[1][3] = 1;
	blockMap[2][2] = 2;
	blockMap[2][1] = 1;
}


S_Block::~S_Block()
{
}

void S_Block::render()
{
	for (int i = 0; i < _blockMapHeight; ++i) {
		for (int j = 0; j < _blockMapWidth; j++) {
			if (blockMap[j][i] != 0) {

				// Draw Individual Blocks
				SDL_Rect sBlock_Block;
				sBlock_Block.h = BLOCK_SIZE;
				sBlock_Block.w = BLOCK_SIZE;
				sBlock_Block.x = _x + (i * BLOCK_SIZE);
				sBlock_Block.y = _y + (j * BLOCK_SIZE);

				// Render Purple T
				SDL_SetRenderDrawColor(_renderer, 0, 255, 0, 255);
				SDL_RenderFillRect(_renderer, &sBlock_Block);
				SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
				SDL_RenderDrawRect(_renderer, &sBlock_Block);
			}
		}
	}
}
