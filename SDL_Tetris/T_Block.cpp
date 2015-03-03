#include "T_Block.h"
#include <iostream>


T_Block::T_Block(SDL_Renderer* _renderer, Board* _gameBoard) : _renderer(_renderer), _gameBoard(_gameBoard)
{
	_xPos = 214;
	_yPos = 150;
	tBlock[0][1] = 1;
	tBlock[1][1] = 1;
	tBlock[2][1] = 1;
	tBlock[1][2] = 1;

	// Create Block Texture
	defineBlock();
}

T_Block::~T_Block()
{
}

bool T_Block::checkCollision()
{
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (tBlock[j][i] == 1) {

				targetRect.x = _xPos + (i * Tetromino::_blockSize);
				targetRect.y = _yPos + (j * Tetromino::_blockSize);

				int checkX = ((targetRect.x - 150) / 16);
				int checkY = (((targetRect.y - 150) / 16) + 1);

				std::cout << checkY << std::endl;

				if (_gameBoard->_board[checkX][checkY] != 0) {
					return true;
				}
			}
		}
	}
	return false;
}

bool T_Block::checkValidLateralMovement()
{
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (tBlock[j][i] == 1) {

				targetRect.x = _xPos + (i * Tetromino::_blockSize);
				targetRect.y = _yPos + (j * Tetromino::_blockSize);

				int checkX = ((targetRect.x - 150) / 16);
				int checkY = (((targetRect.y - 150) / 16));

				std::cout << checkY << std::endl;

				if (_gameBoard->_board[checkX + 1][checkY] != 0) {
					return false;
				}

				if (_gameBoard->_board[checkX - 1][checkY] != 0) {
					return false;
				}
				
			}
		}
	}
	return true;
}

void T_Block::render()
{
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (tBlock[j][i] != 0) {

				targetRect.h = Tetromino::_blockHeight;
				targetRect.w = Tetromino::_blockWidth;
				targetRect.x = _xPos + (i * Tetromino::_blockSize);
				targetRect.y = _yPos + (j * Tetromino::_blockSize);

				SDL_SetRenderDrawColor(_renderer, 255, 0, 0, 255);
				SDL_RenderCopy(_renderer, tetrominoTexture, NULL, &targetRect);

			}
		}
	}
}

void T_Block::defineBlock()
{

	tetrominoTexture = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, Tetromino::_blockWidth, Tetromino::_blockHeight);
	SDL_SetTextureBlendMode(tetrominoTexture, SDL_BLENDMODE_ADD);

	SDL_Rect tetromino;

	tetromino.x = 0;
	tetromino.y = 0;
	tetromino.w = Tetromino::_blockWidth;
	tetromino.h = Tetromino::_blockHeight;

	_tetromino = tetromino;

	SDL_SetRenderTarget(_renderer, tetrominoTexture);
	SDL_SetRenderDrawColor(_renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(_renderer, &tetromino);
}

void T_Block::placeBrick()
{
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (tBlock[j][i] == 1) {

				targetRect.x = _xPos + (i * Tetromino::_blockSize);
				targetRect.y = _yPos + (j * Tetromino::_blockSize);

				_gameBoard->_board[((targetRect.x - 150) / 16)][((targetRect.y - 150) / 16)] = 1;
			}
		}
	}
}

void T_Block::update()
{
	render();
}
