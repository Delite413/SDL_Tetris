#pragma once

#include <SDL/SDL.h>

#include "Board.h"
#include "Tetromino.h"

class T_Block :
	public Tetromino
{
public:
	T_Block(SDL_Renderer* _renderer, Board* _gameBoard);
	~T_Block();

	bool     checkCollision(int xPos, int yPos);
	bool     checkRotationCollision(int xPos, int yPos, int tempArray[4][4]);
	void	 copyToBlockMap(int tempArray[4][4]);
	void     placeBricks();
	void     render();
	void	 rotateClockwise();

	//Wall Kick Checks

	void	 upToRight(int tempBlockMap[4][4], int tempArray[4][4]);
	void	 rightToDown(int tempBlockMap[4][4], int tempArray[4][4]);
	void	 downToLeft(int tempBlockMap[4][4], int tempArray[4][4]);
	void	 leftToUp(int tempBlockMap[4][4], int tempArray[4][4]);

private:
	Board* _gameBoard;
	SDL_Renderer* _renderer;

};

