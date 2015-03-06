#include "T_Block.h"

T_Block::T_Block(SDL_Renderer* _renderer, Board* _gameBoard) : _renderer(_renderer), _gameBoard(_gameBoard), _pivotCoords(1, 1)
{
	// Set Initial Starting Positions
	_startingXPos = 230;
	_startingYPos = 150;
	_x = _startingXPos;
	_y = _startingYPos;
	/* 
	T-Block Map
	    [0]
	 [1][2][3]
	*/
	blockMap[0][1] = 1;
	blockMap[1][0] = 1;
	blockMap[1][1] = 1;
	blockMap[1][2] = 1;
}

T_Block::~T_Block()
{

}

bool T_Block::checkCollision()
{
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (blockMap[j][i] == 1) {

				// Draw Individual Blocks
				SDL_Rect checkPosition;

				// Check Below Each Brick
				checkPosition.x = _x + (i * BLOCK_SIZE);
				checkPosition.y = _y + (j * BLOCK_SIZE);

				Vector2D convertedCoords = convertCoords(checkPosition.x, checkPosition.y);

				if (_gameBoard->_board[convertedCoords.getX()][convertedCoords.getY() + 1] != 0) {
					return true;
				}

			}
		}
	}
	return false;
}

void T_Block::placeBricks()
{
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (blockMap[j][i] == 1) {

				// Draw Individual Blocks
				SDL_Rect placeBlock;

				placeBlock.x = _x + (i * BLOCK_SIZE);
				placeBlock.y = _y + (j * BLOCK_SIZE);

				Vector2D convertedCoords = convertCoords(placeBlock.x, placeBlock.y);

				// Set overlapping Squares on Board to 1
				_gameBoard->_board[convertedCoords.getX()][convertedCoords.getY()] = 1;
			}
		}
	}
}

void T_Block::render()
{
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (blockMap[j][i] == 1) {

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
