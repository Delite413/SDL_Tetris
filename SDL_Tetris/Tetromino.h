#pragma once
#include <SDL/SDL.h>

#include "Vector2D.h"

class Tetromino
{
public:
	Tetromino();
	virtual ~Tetromino();

	int blockMap[3][3];
	
	// Virtual Methods
	virtual bool     checkCollision() = 0; 
	virtual void	 placeBricks() = 0;
	virtual void     render() = 0;

	// Native Method
	Vector2D		 convertCoords(int x, int y);
	int              getX() { return _x; }
	int              getY() { return _y; }
	int              getStartingX() { return _startingXPos; }
	int              getStartingY() { return _startingYPos; }
	void             moveBlock();
	void             rotateClockwise();
	void             setX(int x) { _x = x; }
	void             setY(int y) { _y = y; }
	void			 update();
	
protected:
	const int BLOCK_SIZE = 20;

	int _blockMapWidth;
	int _blockMapHeight;
	int _x;
	int _y;
	int _startingXPos;
	int _startingYPos;

private:
};

