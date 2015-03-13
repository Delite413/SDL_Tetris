#include "Tetromino.h"
#include "I_Block.h"
#include "J_Block.h"
#include "L_Block.h"
#include "O_Block.h"
#include "S_Block.h"
#include "T_Block.h"
#include "Z_Block.h"

#include <iostream>
#include <typeinfo>

Tetromino::Tetromino() : blockState(BlockState::UP)
{
	// Set all Values of blockMap to 0
	for (int i = 0; i < _blockMapHeight; ++i) {
		for (int j = 0; j < _blockMapHeight; j++) {
			blockMap[j][i] = 0;
		}
	}
}

Tetromino::~Tetromino()
{

}

void Tetromino::moveBlock()
{
	// Move Block Down 20 Pixels
	this->setY(this->getY() + 20);
}

void Tetromino::placeBricks(Board* _gameBoard, const type_info &type)
{
	for (int i = 0; i < _blockMapHeight; ++i) {
		for (int j = 0; j < _blockMapWidth; j++) {
			if (blockMap[j][i] != 0) {

				// Draw Individual Blocks
				SDL_Rect placeBlock;

				placeBlock.x = _x + (i * BLOCK_SIZE);
				placeBlock.y = _y + (j * BLOCK_SIZE);

				Vector2D convertedCoords = convertCoords(placeBlock.x, placeBlock.y);

				// Set overlapping Squares on Board to 1
				if (type == typeid(T_Block)) {
					_gameBoard->_board[convertedCoords.getX()][convertedCoords.getY()] = 1;
				}
				else if (type == typeid(J_Block)) {
					_gameBoard->_board[convertedCoords.getX()][convertedCoords.getY()] = 2;
				}
				else if (type == typeid(S_Block)) {
					_gameBoard->_board[convertedCoords.getX()][convertedCoords.getY()] = 3;
				}
				else if (type == typeid(Z_Block)) {
					_gameBoard->_board[convertedCoords.getX()][convertedCoords.getY()] = 4;
				}
				else if (type == typeid(L_Block)) {
					_gameBoard->_board[convertedCoords.getX()][convertedCoords.getY()] = 5;
				}
				else if (type == typeid(I_Block)) {
					_gameBoard->_board[convertedCoords.getX()][convertedCoords.getY()] = 6;
				}
				else if (type == typeid(O_Block)) {
					_gameBoard->_board[convertedCoords.getX()][convertedCoords.getY()] = 7;
				}
			}
		}
	}
}

void Tetromino::rotateClockwise(Board* _gameBoard)
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

void Tetromino::update()
{
}
// Note: Clean Up code Later. Pass in Offsets as Arguments as opposed to hard coding.
void Tetromino::upToRight(int tempBlockMap[5][5], int tempArray[5][5], Board* _gameBoard)
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
	// Check ( -1, +1 )
	else if (checkRotationCollision(_x - BLOCK_SIZE, _y + BLOCK_SIZE, tempArray, _gameBoard) == false) {
		_x -= BLOCK_SIZE;
		_y += BLOCK_SIZE;
		copyToBlockMap(tempArray);
	}
	// Check ( 0, -2 )
	else if (checkRotationCollision(_x, _y - (BLOCK_SIZE * 2), tempArray, _gameBoard) == false) {
		_y -= (BLOCK_SIZE * 2);
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

	blockState = BlockState::RIGHT;
}

void Tetromino::rightToDown(int tempBlockMap[5][5], int tempArray[5][5], Board* _gameBoard)
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
	// Check ( +1, -1 )
	else if (checkRotationCollision(_x + BLOCK_SIZE, _y - BLOCK_SIZE, tempArray, _gameBoard) == false) {
		_x += BLOCK_SIZE;
		_y -= BLOCK_SIZE;
		copyToBlockMap(tempArray);
	}
	// Check ( 0, 2 )
	else if (checkRotationCollision(_x, _y + (BLOCK_SIZE * 2), tempArray, _gameBoard) == false) {
		_y += (BLOCK_SIZE * 2);
		copyToBlockMap(tempArray);
	}
	// Check ( 1, 2 )
	else if (checkRotationCollision(_x + BLOCK_SIZE, _y + (BLOCK_SIZE * 2), tempArray, _gameBoard) == false) {
		_x += BLOCK_SIZE;
		_y += (BLOCK_SIZE * 2);
		copyToBlockMap(tempArray);
	}
	else {
		copyToBlockMap(tempBlockMap);
	}

	blockState = BlockState::DOWN;
}

void Tetromino::downToLeft(int tempBlockMap[5][5], int tempArray[5][5], Board* _gameBoard)
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
	// Check ( +1, +1 )
	else if (checkRotationCollision(_x + BLOCK_SIZE, _y + BLOCK_SIZE, tempArray, _gameBoard) == false) {
		_x += BLOCK_SIZE;
		_y += BLOCK_SIZE;
		copyToBlockMap(tempArray);
	}
	// Check ( 0, -2 )
	else if (checkRotationCollision(_x, _y - (BLOCK_SIZE * 2), tempArray, _gameBoard) == false) {
		_y -= (BLOCK_SIZE * 2);
		copyToBlockMap(tempArray);
	}
	// Check ( 1, -2 )
	else if (checkRotationCollision(_x + BLOCK_SIZE, _y - (BLOCK_SIZE * 2), tempArray, _gameBoard) == false) {
		_x += BLOCK_SIZE;
		_y -= (BLOCK_SIZE * 2);
		copyToBlockMap(tempArray);
	}
	else {
		copyToBlockMap(tempBlockMap);
	}

	blockState = BlockState::LEFT;
}

void Tetromino::leftToUp(int tempBlockMap[5][5], int tempArray[5][5], Board* _gameBoard)
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
	// Check ( -1, -1 )
	else if (checkRotationCollision(_x - BLOCK_SIZE, _y - BLOCK_SIZE, tempArray, _gameBoard) == false) {
		_x -= BLOCK_SIZE;
		_y -= BLOCK_SIZE;
		copyToBlockMap(tempArray);
	}
	// Check ( 0, 2 )
	else if (checkRotationCollision(_x, _y + (BLOCK_SIZE * 2), tempArray, _gameBoard) == false) {
		_y += (BLOCK_SIZE * 2);
		copyToBlockMap(tempArray);
	}
	// Check ( -1, 2 )
	else if (checkRotationCollision(_x - BLOCK_SIZE, _y + (BLOCK_SIZE * 2), tempArray, _gameBoard) == false) {
		_x -= BLOCK_SIZE;
		_y += (BLOCK_SIZE * 2);
		copyToBlockMap(tempArray);
	}
	else {
		copyToBlockMap(tempBlockMap);
	}

	blockState = BlockState::UP;
}

bool Tetromino::checkCollision(int xPos, int yPos, Board* _gameBoard)
{
	for (int i = 0; i < _blockMapHeight; ++i) {
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

bool Tetromino::checkRotationCollision(int xPos, int yPos, int tempArray[5][5], Board* _gameBoard)
{
	for (int i = 0; i < _blockMapHeight; ++i) {
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

Vector2D Tetromino::convertCoords(int x, int y)
{
	//Convert Global Coordinates to Board Array Coordinates
	Vector2D boardCoords;
	boardCoords.setX((x - Board::SCREEN_X_OFFSET) / BLOCK_SIZE);
	boardCoords.setY((y - Board::SCREEN_Y_OFFSET) / BLOCK_SIZE);
	return boardCoords;
}

void Tetromino::copyToBlockMap(int tempArray[5][5])
{
	//Copy TempArray to BlockMap
	for (int i = 0; i < _blockMapHeight; ++i) {
		for (int j = 0; j < _blockMapWidth; j++) {
			blockMap[j][i] = tempArray[j][i];
		}
	}
}
