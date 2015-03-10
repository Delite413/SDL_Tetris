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

bool T_Block::checkRotationCollision(int xPos, int yPos,int tempArray[4][4])
{
	for (int i = 0; i < _blockMapHeight; i++) {
		for (int j = 0; j < _blockMapWidth; j++) {
			if (tempArray[j][i] != 0) {

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

void T_Block::copyToBlockMap(int tempArray[4][4])
{
	//Copy TempArray to BlockMap
	for (int i = 0; i < _blockMapHeight; i++) {
		for (int j = 0; j < _blockMapWidth; j++) {
			blockMap[j][i] = tempArray[j][i];
		}
	}
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

void T_Block::rotateClockwise()
{
	// Create Temporary Array and Initialize everything to 0
	int tempArray[4][4] = {};
	int tempBlockMap[4][4] = {};

	//Pivot Point Declaration
	Vector2D pivotPoint;

	// Find Pivot Point
	for (int i = 0; i < _blockMapHeight; i++) {
		for (int j = 0; j < _blockMapWidth; j++) {
			if (blockMap[j][i] == 2) {
				pivotPoint.setX(j);
				pivotPoint.setY(i);
			}
		}
	}

	// Rotate All Other Squares
	for (int i = 0; i < _blockMapHeight; i++) {
		for (int j = 0; j < _blockMapWidth; j++) {
			if (blockMap[j][i] == 1) {

				/*
				Matrix Math
				| 0 1 |
				|-1 0 |   Clockwise Rotation
				*/

				//Matrix Declaration
				int matrixTL = 0;
				int matrixTR = -1;
				int matrixBL = 1;
				int matrixBR = 0;

				// Subtract Pivot Point
				Vector2D rotatedCoordinates;

				rotatedCoordinates.setX(i - pivotPoint.getX());
				rotatedCoordinates.setY(j - pivotPoint.getY());

				// Multiply by Matrix

				int rotatedGlobalX = (rotatedCoordinates.getX() * matrixTL) + (rotatedCoordinates.getY() * matrixTR);
				int rotatedGlobalY = (rotatedCoordinates.getX() * matrixBL) + (rotatedCoordinates.getY() * matrixBR);

				// Add Pivot Point to get Relative
				int rotatedRelativeX = rotatedGlobalX + pivotPoint.getX();
				int rotatedRelativeY = rotatedGlobalY + pivotPoint.getY();

				// Store Results into Temp Array
				tempArray[rotatedRelativeY][rotatedRelativeX] = 1;

				//Clear current Position
				tempBlockMap[j][i] = blockMap[j][i];
;				blockMap[j][i] = 0;
			}
		}
	}
	//Set Pivot Point
	tempBlockMap[2][2] = 2;
	tempArray[2][2] = 2;

	// WallKick Checks
	switch (blockState) {
	case BlockState::UP:
		upToRight(tempBlockMap, tempArray);
		break;
	case BlockState::RIGHT:
		rightToDown(tempBlockMap, tempArray);
		break;
	case BlockState::DOWN:
		downToLeft(tempBlockMap, tempArray);
		break;
	case BlockState::LEFT:
		leftToUp(tempBlockMap, tempArray);
	default:
		break;
	}
}

void T_Block::upToRight(int tempBlockMap[4][4], int tempArray[4][4])
{
	// Check (0,0)
	if (checkRotationCollision(_x, _y, tempArray) == false) {
		copyToBlockMap(tempArray);
	}
	// Check ( -1, 0 )
	else if (checkRotationCollision(_x - BLOCK_SIZE, _y, tempArray) == false) {
		_x -= BLOCK_SIZE;
		copyToBlockMap(tempArray);
	}
	// Check ( -1, +1 )
	else if (checkRotationCollision(_x - BLOCK_SIZE, _y + BLOCK_SIZE, tempArray) == false) {
		_x -= BLOCK_SIZE;
		_y += BLOCK_SIZE;
		copyToBlockMap(tempArray);
	}
	// Check ( 0, -2 )
	else if (checkRotationCollision(_x, _y - (BLOCK_SIZE * 2), tempArray) == false) {
		_y -= (BLOCK_SIZE * 2);
		copyToBlockMap(tempArray);
	}
	// Check ( -1, -2 )
	else if (checkRotationCollision(_x - BLOCK_SIZE, _y - (BLOCK_SIZE * 2), tempArray) == false) {
		_x -= BLOCK_SIZE;
		_y -= (BLOCK_SIZE * 2);
		copyToBlockMap(tempArray);
	}
	else {
		copyToBlockMap(tempBlockMap);
	}

	blockState = BlockState::RIGHT;
}

void T_Block::rightToDown(int tempBlockMap[4][4], int tempArray[4][4])
{
	// Check (0,0)
	if (checkRotationCollision(_x, _y, tempArray) == false) {
		copyToBlockMap(tempArray);
	}
	// Check ( +1, 0 )
	else if (checkRotationCollision(_x + BLOCK_SIZE, _y, tempArray) == false) {
		_x += BLOCK_SIZE;
		copyToBlockMap(tempArray);
	}
	// Check ( +1, -1 )
	else if (checkRotationCollision(_x + BLOCK_SIZE, _y - BLOCK_SIZE, tempArray) == false) {
		_x += BLOCK_SIZE;
		_y -= BLOCK_SIZE;
		copyToBlockMap(tempArray);
	}
	// Check ( 0, 2 )
	else if (checkRotationCollision(_x, _y + (BLOCK_SIZE * 2), tempArray) == false) {
		_y += (BLOCK_SIZE * 2);
		copyToBlockMap(tempArray);
	}
	// Check ( 1, 2 )
	else if (checkRotationCollision(_x + BLOCK_SIZE, _y + (BLOCK_SIZE * 2), tempArray) == false) {
		_x += BLOCK_SIZE;
		_y += (BLOCK_SIZE * 2);
		copyToBlockMap(tempArray);
	}
	else {
		copyToBlockMap(tempBlockMap);
	}

	blockState = BlockState::DOWN;
}

void T_Block::downToLeft(int tempBlockMap[4][4], int tempArray[4][4])
{
	// Check (0,0)
	if (checkRotationCollision(_x, _y, tempArray) == false) {
		copyToBlockMap(tempArray);
	}
	// Check ( +1, 0 )
	else if (checkRotationCollision(_x + BLOCK_SIZE, _y, tempArray) == false) {
		_x += BLOCK_SIZE;
		copyToBlockMap(tempArray);
	}
	// Check ( +1, +1 )
	else if (checkRotationCollision(_x + BLOCK_SIZE, _y + BLOCK_SIZE, tempArray) == false) {
		_x += BLOCK_SIZE;
		_y += BLOCK_SIZE;
		copyToBlockMap(tempArray);
	}
	// Check ( 0, -2 )
	else if (checkRotationCollision(_x, _y - (BLOCK_SIZE * 2), tempArray) == false) {
		_y -= (BLOCK_SIZE * 2);
		copyToBlockMap(tempArray);
	}
	// Check ( 1, -2 )
	else if (checkRotationCollision(_x + BLOCK_SIZE, _y - (BLOCK_SIZE * 2), tempArray) == false) {
		_x += BLOCK_SIZE;
		_y -= (BLOCK_SIZE * 2);
		copyToBlockMap(tempArray);
	}
	else {
		copyToBlockMap(tempBlockMap);
	}

	blockState = BlockState::LEFT;
}

void T_Block::leftToUp(int tempBlockMap[4][4], int tempArray[4][4])
{
	// Check (0,0)
	if (checkRotationCollision(_x, _y, tempArray) == false) {
		copyToBlockMap(tempArray);
	}
	// Check ( -1, 0 )
	else if (checkRotationCollision(_x - BLOCK_SIZE, _y, tempArray) == false) {
		_x -= BLOCK_SIZE;
		copyToBlockMap(tempArray);
	}
	// Check ( -1, -1 )
	else if (checkRotationCollision(_x - BLOCK_SIZE, _y - BLOCK_SIZE, tempArray) == false) {
		_x -= BLOCK_SIZE;
		_y -= BLOCK_SIZE;
		copyToBlockMap(tempArray);
	}
	// Check ( 0, 2 )
	else if (checkRotationCollision(_x, _y + (BLOCK_SIZE * 2), tempArray) == false) {
		_y += (BLOCK_SIZE * 2);
		copyToBlockMap(tempArray);
	}
	// Check ( -1, 2 )
	else if (checkRotationCollision(_x - BLOCK_SIZE, _y + (BLOCK_SIZE * 2), tempArray) == false) {
		_x -= BLOCK_SIZE;
		_y += (BLOCK_SIZE * 2);
		copyToBlockMap(tempArray);
	}
	else {
		copyToBlockMap(tempBlockMap);
	}

	blockState = BlockState::UP;
}
