#pragma once
#include <SDL/SDL.h>

#include "Vector2D.h"

enum class BlockState {UP,RIGHT,LEFT,DOWN};

class Tetromino
{
public:
	Tetromino();
	virtual ~Tetromino();

	int				 blockMap[4][4];

	// Virtual Methods
	virtual bool     checkCollision(int xPos, int yPos) = 0;
	virtual void     copyToBlockMap(int tempArray[4][4]) = 0;
	virtual void	 placeBricks() = 0;
	virtual void     render() = 0;
	virtual void     rotateClockwise() = 0;

	// Native Method
	Vector2D		 convertCoords(int x, int y);
	int              getX() { return _x; }
	int              getY() { return _y; }
	int              getStartingX() { return _startingXPos; }
	int              getStartingY() { return _startingYPos; }
	void             moveBlock();
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

	BlockState blockState;

private:
};

