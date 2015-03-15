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
	void render(unsigned long &playerScore, int &multiplier, unsigned int &linesDeleted);

private:
	SDL_Color _comboColor;
	SDL_Color _defaultColor;

	SDL_Renderer* _renderer;

	// Score Related
	SDL_Texture* _scoreTexture;
	TTF_Font* _scoreFont;
};

