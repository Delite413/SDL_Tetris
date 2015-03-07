#include "Board.h"
#include "Tetromino.h"
#include "T_Block.h"

#include <iostream>

Tetromino::Tetromino()
{
	// Set all Values of blockMap to 0
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			blockMap[j][i] = 0;
		}
	}
}

Tetromino::~Tetromino()
{

}

void Tetromino::moveBlock()
{
	this->setY(this->getY() + 20);
}

void Tetromino::rotateClockwise()
{
	// Create Temporary Array and Initialize everything to 0
	int tempArray[3][3] = {};

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
				blockMap[j][i] = 0;

			}
		}
	}
	//Set Pivot Point
	tempArray[1][1] = 2;

	//Copy TempArray to
	for (int i = 0; i < _blockMapHeight; i++) {
		for (int j = 0; j < _blockMapWidth; j++) {
			blockMap[j][i] = tempArray[j][i];
		}
	}

}

void Tetromino::update()
{
}

Vector2D Tetromino::convertCoords(int x, int y)
{
	//Convert Global Coordinates to Board Array Coordinates
	Vector2D boardCoords;
	boardCoords.setX((x - Board::SCREEN_X_OFFSET) / BLOCK_SIZE);
	boardCoords.setY((y - Board::SCREEN_Y_OFFSET) / BLOCK_SIZE);
	return boardCoords;
}
