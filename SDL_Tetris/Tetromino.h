#pragma once
#include <SDL/SDL.h>

#include "Board.h"
#include "Vector2D.h"

enum class BlockState {UP,RIGHT,LEFT,DOWN};

class Tetromino
{
public:
	Tetromino();
	virtual ~Tetromino();

	int				 blockMap[4][4];

	// Virtual Methods
	virtual void     render() = 0;

	// Native Method
	bool			 checkCollision(int xPos, int yPos, Board* _gameBoard);
	bool		     checkRotationCollision(int xPos, int yPos, int tempArray[4][4], Board* _gameBoard);
	Vector2D		 convertCoords(int x, int y);
	void			 copyToBlockMap(int tempArray[4][4]);
	int              getX() { return _x; }
	int              getY() { return _y; }
	int              getStartingX() { return _startingXPos; }
	int              getStartingY() { return _startingYPos; }
	void             moveBlock();
	void			 placeBricks(Board* _gameBoard);
	void			 rotateClockwise(Board* _gameBoard);
	void             setX(int x) { _x = x; }
	void             setY(int y) { _y = y; }
	void			 update();

	//Wall Kick Checks

	void	 upToRight(int tempBlockMap[4][4], int tempArray[4][4], Board* _gameBoard);
	void	 rightToDown(int tempBlockMap[4][4], int tempArray[4][4], Board* _gameBoard);
	void	 downToLeft(int tempBlockMap[4][4], int tempArray[4][4], Board* _gameBoard);
	void	 leftToUp(int tempBlockMap[4][4], int tempArray[4][4], Board* _gameBoard);
	
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

