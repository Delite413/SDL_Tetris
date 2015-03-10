#include "Board.h"
#include "Tetromino.h"
#include "T_Block.h"

#include <iostream>

Tetromino::Tetromino() : blockState(BlockState::UP)
{
	// Set all Values of blockMap to 0
	for (int i = 0; i < _blockMapHeight; i++) {
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
	this->setY(this->getY() + 20);
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

