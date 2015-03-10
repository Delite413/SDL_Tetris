#include "T_Block.h"

#include <iostream>
T_Block::T_Block(SDL_Renderer* _renderer, Board* _gameBoard) : _renderer(_renderer), _gameBoard(_gameBoard)
{
	// Set Initial Starting Positions
	_startingXPos = 230;
	_startingYPos = 150;
	_x = _startingXPos;
	_y = _startingYPos;
	_blockMapWidth = 3;
	_blockMapHeight = 3;
	/* 
	T-Block Map
	    [0]
	 [1][2][3]
	*/
	blockMap[0][1] = 1;
	blockMap[1][0] = 1;
	blockMap[1][1] = 2;
	blockMap[1][2] = 1;
}

T_Block::~T_Block()
{

}

bool T_Block::checkCollision(int xPos, int yPos)
{
	for (int i = 0; i < _blockMapHeight; i++) {
		for (int j = 0; j < _blockMapWidth; j++) {
			if (blockMap[j][i] != 0) {

				// Draw Individual Blocks
				SDL_Rect checkPosition;

				// Check Each Brick
				checkPosition.x = xPos + (i * BLOCK_SIZE);
				checkPosition.y = yPos + (j * BLOCK_SIZE);

				Vector2D convertedCoords = convertCoords(checkPosition.x, checkPosition.y);

				if (_gameBoard->_board[convertedCoords.getX()][convertedCoords.getY()] != 0) {
					std::cout << "Collision Detected!" << std::endl;
					return true;
				}
			}
		}
	}
	return false;
}

Vector2D T_Block::checkRotationCollision(int xPos, int yPos)
{
	Vector2D transformedBlock(1, 1);
	return transformedBlock;
}

void T_Block::placeBricks()
{
	for (int i = 0; i < _blockMapHeight; i++) {
		for (int j = 0; j < _blockMapWidth; j++) {
			if (blockMap[j][i] != 0) {

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
