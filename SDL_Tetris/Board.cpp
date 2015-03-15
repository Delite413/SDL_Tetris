#include "Board.h"

#include <iostream>


Board::Board(SDL_Renderer* _renderer) : _renderer(_renderer), _blockSize(20)
{
	// Create Empty Board
		for (int i = 0; i < BOARD_WIDTH; ++i) {
			for (int j = 0; j < BOARD_HEIGHT; j++) {
				_board[i][j] = 0;
		}
	}
	// Create Vertical Borders
	for (int i = 0; i < BOARD_HEIGHT; ++i) {
			_board[0][i] = 8;
			_board[11][i] = 8;
	}
	// Create Bottom Border
	for (int i = 0; i < BOARD_WIDTH; ++i) {
		_board[i][20] = 8;
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

bool Board::checkForLines(unsigned int &_linesDeleted, unsigned long &playerScore)
{
	int deletedLines = 0;

	for (int i = 0; i < 20; ++i) {
		int filledBlocks = 0;

		for (int j = 1; j < 11 ; j++) {
			if (_board[j][i] != 0) {
				++filledBlocks;
			}

			if (filledBlocks == 10) {
				deleteLine(i);
				++deletedLines;
			}
		}
	}
	if (deletedLines != 0) {
		if (deletedLines == 4) {
			playerScore += 100;
		}
		else if (deletedLines == 3) {
			playerScore += 50;
		}
		else if (deletedLines == 2) {
			playerScore += 25;
		}
		else {
			playerScore += 10;
		}

		_linesDeleted += deletedLines;
		return true;
	}
	else {
		return false;
	}
}

void Board::checkGameOver()
{
	for (int i = 1; i < BOARD_WIDTH - 1; ++i) {

	}
}

void Board::deleteLine(int line)
{
	for (int i = line; i > 0; i--) {
		for (int j = 1; j < BOARD_WIDTH - 1; j++) {
			_board[j][i] = _board[j][i-1];
		}
	}
}

void Board::render()
{
	// Prep boardTexture
	SDL_SetRenderTarget(_renderer, boardTexture);
	SDL_SetTextureBlendMode(boardTexture, SDL_BLENDMODE_BLEND);

	for (int i = 0; i < BOARD_WIDTH; ++i) {
		for (int j = 0; j < BOARD_HEIGHT; j++) {
			if (_board[i][j] == 0) {
				SDL_Rect emptyBlock = { SCREEN_X_OFFSET + i * _blockSize, SCREEN_Y_OFFSET + j * _blockSize, _blockSize, _blockSize };
				SDL_SetRenderDrawColor(_renderer, 50, 50, 50, 255);
				SDL_RenderDrawRect(_renderer, &emptyBlock);
			}
			else if (_board[i][j] == 1) {
				// Tetromino Piece 1
				SDL_Rect t_blockRect = { SCREEN_X_OFFSET + i * _blockSize, SCREEN_Y_OFFSET + j * _blockSize, _blockSize, _blockSize };
				SDL_SetRenderDrawColor(_renderer, 255, 0, 255, 255);
				SDL_RenderFillRect(_renderer, &t_blockRect);
				SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
				SDL_RenderDrawRect(_renderer, &t_blockRect);
			}
			else if (_board[i][j] == 2) {
				// Tetromino Piece 2
				SDL_Rect j_blockRect = { SCREEN_X_OFFSET + i * _blockSize, SCREEN_Y_OFFSET + j * _blockSize, _blockSize, _blockSize };
				SDL_SetRenderDrawColor(_renderer, 0, 0, 255, 255);
				SDL_RenderFillRect(_renderer, &j_blockRect);
				SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
				SDL_RenderDrawRect(_renderer, &j_blockRect);
			}
			else if (_board[i][j] == 3) {
				// Tetromino Piece 3
				SDL_Rect s_blockRect = { SCREEN_X_OFFSET + i * _blockSize, SCREEN_Y_OFFSET + j * _blockSize, _blockSize, _blockSize };
				SDL_SetRenderDrawColor(_renderer, 0, 255, 0, 255);
				SDL_RenderFillRect(_renderer, &s_blockRect);
				SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
				SDL_RenderDrawRect(_renderer, &s_blockRect);
			}
			else if (_board[i][j] == 4) {
				// Tetromino Piece 4
				SDL_Rect z_blockRect = { SCREEN_X_OFFSET + i * _blockSize, SCREEN_Y_OFFSET + j * _blockSize, _blockSize, _blockSize };
				SDL_SetRenderDrawColor(_renderer, 255, 0, 0, 255);
				SDL_RenderFillRect(_renderer, &z_blockRect);
				SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
				SDL_RenderDrawRect(_renderer, &z_blockRect);
			}
			else if (_board[i][j] == 5) {
				// Tetromino Piece 5
				SDL_Rect l_blockRect = { SCREEN_X_OFFSET + i * _blockSize, SCREEN_Y_OFFSET + j * _blockSize, _blockSize, _blockSize };
				SDL_SetRenderDrawColor(_renderer, 255, 102, 0, 255);
				SDL_RenderFillRect(_renderer, &l_blockRect);
				SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
				SDL_RenderDrawRect(_renderer, &l_blockRect);
			}
			else if (_board[i][j] == 6) {
				// Tetromino Piece 6
				SDL_Rect i_blockRect = { SCREEN_X_OFFSET + i * _blockSize, SCREEN_Y_OFFSET + j * _blockSize, _blockSize, _blockSize };
				SDL_SetRenderDrawColor(_renderer, 51, 153, 255, 255);
				SDL_RenderFillRect(_renderer, &i_blockRect);
				SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
				SDL_RenderDrawRect(_renderer, &i_blockRect);
			}
			else if (_board[i][j] == 7) {
				// Tetromino Piece 7
				SDL_Rect o_blockRect = { SCREEN_X_OFFSET + i * _blockSize, SCREEN_Y_OFFSET + j * _blockSize, _blockSize, _blockSize };
				SDL_SetRenderDrawColor(_renderer, 255, 204, 0, 255);
				SDL_RenderFillRect(_renderer, &o_blockRect);
				SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
				SDL_RenderDrawRect(_renderer, &o_blockRect);
			}
			else if (_board[i][j] == 8) {
				// Border
				SDL_Rect borderRect = { SCREEN_X_OFFSET + i * _blockSize, SCREEN_Y_OFFSET + j * _blockSize, _blockSize, _blockSize };
				SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
				SDL_RenderFillRect(_renderer, &borderRect);
			}
		}
	}
}

