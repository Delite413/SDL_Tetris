#pragma once

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <string>

class UserInterface
{
public:
	UserInterface(SDL_Renderer* _renderer);
	~UserInterface();

	void drawScore(unsigned long &playerScore);
	void drawTitle();
	void render(unsigned long &playerScore, int &multiplier, unsigned int &linesDeleted);

private:
	SDL_Color _comboColor;
	SDL_Color _defaultColor;
	SDL_Color _titleColor;

	SDL_Renderer* _renderer;

	// Score Related
	SDL_Texture* _scoreTexture;
	SDL_Texture* _titleTexture;
	TTF_Font* _scoreFont;
	TTF_Font* _titleFont;
};

