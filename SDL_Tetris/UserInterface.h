#pragma once

#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <string>

#include "Board.h"

class UserInterface
{
public:
	UserInterface(SDL_Renderer* _renderer, Board* _gameBoard);
	~UserInterface();

	void drawBlockFrame(const type_info &type);
	void drawLevelFrame(const unsigned int &level);
	void drawLinesFrame(const unsigned int &linesDeleted);
	void drawScore(unsigned long &playerScore);
	void drawTitle();
	void render(unsigned long &playerScore, int &multiplier, unsigned int &level, unsigned int &linesDeleted, const type_info &type);

private:
	Board* _gameBoard;
	SDL_Color _comboColor;
	SDL_Color _defaultColor;
	SDL_Color _titleColor;

	SDL_Renderer* _renderer;

	// Score Related
	SDL_Texture* _levelTexture;
	SDL_Texture* _levelTitleTexture;
	SDL_Texture* _linesTexture;
	SDL_Texture* _linesTitleTexture;
	SDL_Texture* _scoreTexture;
	SDL_Texture* _titleTexture;
	TTF_Font* _blockTitleFont;
	TTF_Font* _defaultFont;
	TTF_Font* _levelNumberFont;
	TTF_Font* _scoreFont;
	TTF_Font* _titleFont;
};

