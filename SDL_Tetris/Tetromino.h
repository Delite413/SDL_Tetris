#pragma once
#include <SDL/SDL.h>
#include <deque>
#include "Board.h"

class Tetromino
{
public:
	Tetromino();
	virtual ~Tetromino();

	//Virtual Functions
	virtual bool checkCollision() = 0;
	virtual bool validLeftLateralMovement() = 0;
	virtual bool validRightLateralMovement() = 0;
	virtual void render() = 0;
	virtual void placeBrick() = 0;
	//Position Related Methods
	float getX() { return _xPos; }
	float getY() { return _yPos; }
	void setX(float newXPos) { _xPos = newXPos; }
	void setY(float newYPos) { _yPos = newYPos;	}

protected:

	float _xPos;
	float _yPos;

	unsigned int _blockSize = 16;
	unsigned int _blockWidth  = 16;
	unsigned int _blockHeight = 16;

private:
	
};

