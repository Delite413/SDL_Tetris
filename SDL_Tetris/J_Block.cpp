#include "J_Block.h"


J_Block::J_Block(SDL_Renderer* _renderer, Board* _gameBoard, int _startingXPos, int _startingYPos) : _renderer(_renderer), _gameBoard(_gameBoard)
{
	// Set Initial Starting Positions
	_x = _startingXPos;
	_y = _startingYPos;
	_blockMapWidth = 4;
	_blockMapHeight = 4;
	/*
	J-Block Map
	[1]
	[2][3][4]
	*/
	blockMap[1][1] = 1;
	blockMap[2][1] = 1;
	blockMap[2][2] = 2;
	blockMap[2][3] = 1;
}


J_Block::~J_Block()
{
}

void J_Block::render()
{
	for (int i = 0; i < _blockMapHeight; ++i) {
		for (int j = 0; j < _blockMapWidth; j++) {
			if (blockMap[j][i] != 0) {

				// Draw Individual Blocks
				SDL_Rect jBlock_Block;
				jBlock_Block.h = BLOCK_SIZE;
				jBlock_Block.w = BLOCK_SIZE;
				jBlock_Block.x = _x + (i * BLOCK_SIZE);
				jBlock_Block.y = _y + (j * BLOCK_SIZE);

				// Render Purple T
				SDL_SetRenderDrawColor(_renderer, 0, 0, 255, 255);
				SDL_RenderFillRect(_renderer, &jBlock_Block);
				SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
				SDL_RenderDrawRect(_renderer, &jBlock_Block);
			}
		}
	}
}
