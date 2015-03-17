#pragma once

#include <SDL/SDL.h>

class Board
{
public:
	Board(SDL_Renderer* _renderer);
	~Board();

	static const int BOARD_WIDTH = 12;
	static const int BOARD_HEIGHT = 21;
	static const int SCREEN_X_OFFSET = 150;
	static const int SCREEN_Y_OFFSET = 150;

	int _board[BOARD_WIDTH][BOARD_HEIGHT];

	SDL_Texture* boardTexture;

	bool checkForLines(unsigned int &_linesDeleted, unsigned long &playerScore);
	void checkGameOver();
	void highlightBlocks(int row);
	void deleteLine(int line);
	void render();
	void update();

private:
	unsigned int _blockSize;

	SDL_Rect _emptyBlock;
	SDL_Renderer* _renderer;

};
