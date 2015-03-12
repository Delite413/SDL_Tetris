#pragma once

#include "Board.h"
#include "Tetromino.h"

#include <SDL/SDL.h>

class I_Block :
	public Tetromino
{
public:
	I_Block(SDL_Renderer* _renderer, Board* _gameBoard);
	~I_Block();

	void render();
	void rotateClockwise(Board* _gameBoard);

	// Overwriting Functions

	void	 upToRight(int tempBlockMap[5][5], int tempArray[5][5], Board* _gameBoard);
	void	 rightToDown(int tempBlockMap[5][5], int tempArray[5][5], Board* _gameBoard);
	void	 downToLeft(int tempBlockMap[5][5], int tempArray[5][5], Board* _gameBoard);
	void	 leftToUp(int tempBlockMap[5][5], int tempArray[5][5], Board* _gameBoard);

private:
	Board* _gameBoard;
	SDL_Renderer* _renderer;
};

