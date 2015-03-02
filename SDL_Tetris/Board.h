#pragma once

#include <SDL/SDL.h>

class Board
{
public:
	Board(SDL_Renderer* _renderer);
	~Board();

	static const int BOARD_WIDTH = 10;
	static const int BOARD_HEIGHT = 20;

	void update();
	void render();

	bool checkValidMove(float x, float y);

	bool _board[BOARD_WIDTH][BOARD_HEIGHT];

	SDL_Texture* boardTexture;

private:
	unsigned int _blockSize;

	SDL_Rect _emptyBlock;
	SDL_Renderer* _renderer;

};
