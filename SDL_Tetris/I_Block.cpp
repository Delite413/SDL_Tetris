#include "I_Block.h"


I_Block::I_Block(SDL_Renderer* _renderer, Board* _gameBoard) : _renderer(_renderer), _gameBoard(_gameBoard)
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
	[1][2][3][4]
	*/
	blockMap[2][4] = 1;
	blockMap[2][1] = 1;
	blockMap[2][2] = 2;
	blockMap[2][3] = 1;
}


I_Block::~I_Block()
{
}

void I_Block::render()
{
	for (int i = 0; i < _blockMapHeight; ++i) {
		for (int j = 0; j < _blockMapWidth; j++) {
			if (blockMap[j][i] != 0) {

				// Draw Individual Blocks
				SDL_Rect iBlock_Block;
				iBlock_Block.h = BLOCK_SIZE;
				iBlock_Block.w = BLOCK_SIZE;
				iBlock_Block.x = _x + (i * BLOCK_SIZE);
				iBlock_Block.y = _y + (j * BLOCK_SIZE);

				// Render Blue I
				SDL_SetRenderDrawColor(_renderer, 51, 153, 255, 255);
				SDL_RenderFillRect(_renderer, &iBlock_Block);
				SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
				SDL_RenderDrawRect(_renderer, &iBlock_Block);
			}
		}
	}
}

void I_Block::rotateClockwise(Board* _gameBoard)
{
	// Create Temporary Array and Initialize everything to 0
	int tempArray[5][5] = {};
	int tempBlockMap[5][5] = {};

	//Pivot Point Declaration
	Vector2D pivotPoint;

	// Find Pivot Point
	for (int i = 0; i < _blockMapHeight; ++i) {
		for (int j = 0; j < _blockMapWidth; j++) {
			if (blockMap[j][i] == 2) {
				pivotPoint.setX(j);
				pivotPoint.setY(i);
			}
		}
	}

	// Rotate All Other Squares
	for (int i = 0; i < _blockMapHeight; ++i) {
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
		upToRight(tempBlockMap, tempArray, _gameBoard);
		break;
	case BlockState::RIGHT:
		rightToDown(tempBlockMap, tempArray, _gameBoard);
		break;
	case BlockState::DOWN:
		downToLeft(tempBlockMap, tempArray, _gameBoard);
		break;
	case BlockState::LEFT:
		leftToUp(tempBlockMap, tempArray, _gameBoard);
	default:
		break;
	}
}

void I_Block::upToRight(int tempBlockMap[5][5], int tempArray[5][5], Board* _gameBoard)
{
	// Check (0,0)
	if (checkRotationCollision(_x, _y, tempArray, _gameBoard) == false) {
		copyToBlockMap(tempArray);
	}
	// Check ( -2, 0 )
	else if (checkRotationCollision(_x - (BLOCK_SIZE * 2), _y, tempArray, _gameBoard) == false) {
		_x -= (BLOCK_SIZE * 2);
		copyToBlockMap(tempArray);
	}
	// Check ( 1, 0 )
	else if (checkRotationCollision(_x + BLOCK_SIZE, _y, tempArray, _gameBoard) == false) {
		_x += BLOCK_SIZE;
		copyToBlockMap(tempArray);
	}
	// Check ( -2, -1 )
	else if (checkRotationCollision(_x - (BLOCK_SIZE * 2), _y - BLOCK_SIZE, tempArray, _gameBoard) == false) {
		_x -= (BLOCK_SIZE * 2);
		_y -= BLOCK_SIZE;
		copyToBlockMap(tempArray);
	}
	// Check ( +1, +2 )
	else if (checkRotationCollision(_x + BLOCK_SIZE, _y + (BLOCK_SIZE * 2), tempArray, _gameBoard) == false) {
		_x += BLOCK_SIZE;
		_y += (BLOCK_SIZE * 2);
		copyToBlockMap(tempArray);
	}
	else {
		copyToBlockMap(tempBlockMap);
	}

	blockState = BlockState::RIGHT;
}

void I_Block::rightToDown(int tempBlockMap[5][5], int tempArray[5][5], Board* _gameBoard)
{
	// Check (0,0)
	if (checkRotationCollision(_x, _y, tempArray, _gameBoard) == false) {
		copyToBlockMap(tempArray);
	}
	// Check ( -1, 0 )
	else if (checkRotationCollision(_x - BLOCK_SIZE, _y, tempArray, _gameBoard) == false) {
		_x -= BLOCK_SIZE;
		copyToBlockMap(tempArray);
	}
	// Check ( +2, 0 )
	else if (checkRotationCollision(_x + (BLOCK_SIZE * 2), _y, tempArray, _gameBoard) == false) {
		_x += (BLOCK_SIZE * 2);
		copyToBlockMap(tempArray);
	}
	// Check ( -1, +2 )
	else if (checkRotationCollision(_x - BLOCK_SIZE, _y + (BLOCK_SIZE * 2), tempArray, _gameBoard) == false) {
		_x -= BLOCK_SIZE;
		_y += (BLOCK_SIZE * 2);
		copyToBlockMap(tempArray);
	}
	// Check ( +2, -1 )
	else if (checkRotationCollision(_x + (BLOCK_SIZE * 2), _y - BLOCK_SIZE, tempArray, _gameBoard) == false) {
		_x += (BLOCK_SIZE * 2);
		_y -= BLOCK_SIZE;
		copyToBlockMap(tempArray);
	}
	else {
		copyToBlockMap(tempBlockMap);
	}

	blockState = BlockState::DOWN;
}

void I_Block::downToLeft(int tempBlockMap[5][5], int tempArray[5][5], Board* _gameBoard)
{
	// Check (0,0)
	if (checkRotationCollision(_x, _y, tempArray, _gameBoard) == false) {
		copyToBlockMap(tempArray);
	}
	// Check ( +2, 0 )
	else if (checkRotationCollision(_x + (BLOCK_SIZE * 2), _y, tempArray, _gameBoard) == false) {
		_x += (BLOCK_SIZE * 2);
		copyToBlockMap(tempArray);
	}
	// Check ( -1, 0 )
	else if (checkRotationCollision(_x - BLOCK_SIZE, _y, tempArray, _gameBoard) == false) {
		_x -= BLOCK_SIZE;
		copyToBlockMap(tempArray);
	}
	// Check ( +2, +1 )
	else if (checkRotationCollision(_x + (BLOCK_SIZE * 2), _y + BLOCK_SIZE, tempArray, _gameBoard) == false) {
		_x += (BLOCK_SIZE * 2);
		_y += BLOCK_SIZE;
		copyToBlockMap(tempArray);
	}
	// Check ( -1, -2 )
	else if (checkRotationCollision(_x - BLOCK_SIZE, _y - (BLOCK_SIZE * 2), tempArray, _gameBoard) == false) {
		_x -= BLOCK_SIZE;
		_y -= (BLOCK_SIZE * 2);
		copyToBlockMap(tempArray);
	}
	else {
		copyToBlockMap(tempBlockMap);
	}

	blockState = BlockState::LEFT;
}

void I_Block::leftToUp(int tempBlockMap[5][5], int tempArray[5][5], Board* _gameBoard)
{
	// Check (0,0)
	if (checkRotationCollision(_x, _y, tempArray, _gameBoard) == false) {
		copyToBlockMap(tempArray);
	}
	// Check ( +1, 0 )
	else if (checkRotationCollision(_x + BLOCK_SIZE, _y, tempArray, _gameBoard) == false) {
		_x += BLOCK_SIZE;
		copyToBlockMap(tempArray);
	}
	// Check ( -2, 0 )
	else if (checkRotationCollision(_x - (BLOCK_SIZE * 2), _y, tempArray, _gameBoard) == false) {
		_x -= (BLOCK_SIZE * 2);
		copyToBlockMap(tempArray);
	}
	// Check ( +1, -2 )
	else if (checkRotationCollision(_x + BLOCK_SIZE, _y - (BLOCK_SIZE * 2), tempArray, _gameBoard) == false) {
		_x += BLOCK_SIZE;
		_y -= (BLOCK_SIZE * 2);
		copyToBlockMap(tempArray);
	}
	// Check ( -2, +1 )
	else if (checkRotationCollision(_x - (BLOCK_SIZE * 2), _y + BLOCK_SIZE, tempArray, _gameBoard) == false) {
		_x -= (BLOCK_SIZE * 2);
		_y += BLOCK_SIZE;
		copyToBlockMap(tempArray);
	}
	else {
		copyToBlockMap(tempBlockMap);
	}

	blockState = BlockState::UP;
}
