#include "Board.h"


Board::Board(SDL_Renderer* _renderer) : _renderer(_renderer), _blockSize(16)
{
	// Create Empty Board

	for (int i = 0; i < BOARD_WIDTH; i++) {
		for (int j = 0; j < BOARD_HEIGHT; j++) {
			_board[i][j] = false;
		}
	}
	// Create Board Texture
	boardTexture = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, NULL, NULL);
}

Board::~Board()
{
}

void Board::update()
{
	render();
}

void Board::render()
{
	for (int i = 0; i < BOARD_WIDTH; i++) {
		for (int j = 0; j < BOARD_HEIGHT; j++) {
			if (_board[i][j] == false) {
				SDL_Rect emptyBlock = { 150 + i * _blockSize, 150 + j * _blockSize, _blockSize, _blockSize };
				SDL_SetRenderTarget(_renderer, boardTexture);
				SDL_SetTextureBlendMode(boardTexture, SDL_BLENDMODE_BLEND);
				SDL_SetRenderDrawColor(_renderer, 0, 255, 0, 255);
				SDL_RenderDrawRect(_renderer, &emptyBlock);
			}
		}
	}
	
}

bool Board::checkValidMove(float x, float y)
{

	return true;
}
