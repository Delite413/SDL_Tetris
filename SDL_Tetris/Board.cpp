#include "Board.h"


Board::Board(SDL_Renderer* _renderer) : _renderer(_renderer), _blockSize(16)
{
	// Create Empty Board

	for (int i = 0; i < BOARD_WIDTH; i++) {
		for (int j = 0; j < BOARD_HEIGHT; j++) {
			_board[i][j] = 0;
		}
	}
	// Create Borders
	for (int i = 0; i < BOARD_HEIGHT; i++) {
			_board[0][i] = 8;
			_board[11][i] = 8;
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
	// Prep boardTexture
	SDL_SetRenderTarget(_renderer, boardTexture);
	SDL_SetTextureBlendMode(boardTexture, SDL_BLENDMODE_BLEND);

	for (int i = 0; i < BOARD_WIDTH; i++) {
		for (int j = 0; j < BOARD_HEIGHT; j++) {
			if (_board[i][j] == 0) {
				SDL_Rect emptyBlock = { 150 + i * _blockSize, 150 + j * _blockSize, _blockSize, _blockSize };
				SDL_SetRenderDrawColor(_renderer, 50, 50, 50, 255);
				SDL_RenderDrawRect(_renderer, &emptyBlock);
			}
			else if (_board[i][j] == 1) {
				// Tetromino Piece 1
				SDL_Rect t_blockRect = { 150 + i * _blockSize, 150 + j * _blockSize, _blockSize, _blockSize };
				SDL_SetRenderDrawColor(_renderer, 255, 0, 0, 255);
				SDL_RenderFillRect(_renderer, &t_blockRect);
			}
			else if (_board[i][j] == 2) {
				// Tetromino Piece 2
			}
			else if (_board[i][j] == 3) {
				// Tetromino Piece 3
			}
			else if (_board[i][j] == 4) {
				// Tetromino Piece 4
			}
			else if (_board[i][j] == 5) {
				// Tetromino Piece 5
			}
			else if (_board[i][j] == 6) {
				// Tetromino Piece 6
			}
			else if (_board[i][j] == 7) {
				// Tetromino Piece 7
			}
			else if (_board[i][j] == 8) {
				// Border
				SDL_Rect borderRect = { 150 + i * _blockSize, 150 + j * _blockSize, _blockSize, _blockSize };
				SDL_SetRenderDrawColor(_renderer, 200, 200, 200, 255);
				SDL_RenderFillRect(_renderer, &borderRect);
			}
		}
	}
}

