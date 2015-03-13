#pragma once

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <string>

class UserInterface
{
public:
	UserInterface(SDL_Renderer* _renderer);
	~UserInterface();

	SDL_Texture* nextBlockTexture;
	SDL_Texture* playerScoreTexture;

	void drawNextBlock();
	void drawScore(unsigned long playerScore, int multiplier);
	void render();

private:
	// Next Block Variables
	int _nextBlockWidth;
	int _nextBlockHeight;
	int _nextBlockXPos;
	int _nextBlockYPos;
	//Player Score Variables
	int _playerScoreWidth;
	int _playerScoreHeight;

	std::string nextText;

	SDL_Color defaultTextColor;
	SDL_Color comboColor;
	SDL_Renderer* _renderer;
	SDL_Surface* nextTextSurface;
	SDL_Texture* _nextBlockTextTexture;
	TTF_Font* nextBlockText;

	void makeText(std::string text, std::string fontName, int fontSize, SDL_Color color, int xPos, int yPos);

};

