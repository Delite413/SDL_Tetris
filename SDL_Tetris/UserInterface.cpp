#include "UserInterface.h"


UserInterface::UserInterface(SDL_Renderer* _renderer) : _renderer(_renderer), _nextBlockWidth(100), _nextBlockHeight(100), _nextBlockXPos(25), _nextBlockYPos(150), _playerScoreWidth(25), _playerScoreHeight(500), nextBlockText(nullptr)
{
	nextBlockTexture = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, _nextBlockWidth, _nextBlockHeight);
	playerScoreTexture = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, _playerScoreWidth, _playerScoreHeight);

	// Set Default Text Color ( White )
	defaultTextColor.r = 255;
	defaultTextColor.g = 255;
	defaultTextColor.b = 255;
	defaultTextColor.a = 255;

	// Set Combo Color (Red)
	comboColor.r = 100;
	comboColor.g = 0;
	comboColor.b = 0;
	comboColor.a = 0;
}


UserInterface::~UserInterface()
{
}

void UserInterface::drawNextBlock()
{
	// Create Block
	SDL_SetRenderTarget(_renderer, nextBlockTexture);
	SDL_SetRenderDrawBlendMode(_renderer, SDL_BLENDMODE_BLEND);

	SDL_Rect nextBlock;
	nextBlock.h = _nextBlockHeight;
	nextBlock.w = _nextBlockWidth;
	nextBlock.x = 0;
	nextBlock.y = 0;

	SDL_SetRenderDrawColor(_renderer, 25, 25, 25, 255);
	SDL_RenderFillRect(_renderer, &nextBlock);
	SDL_SetRenderDrawColor(_renderer, 200, 200, 200, 255);
	SDL_RenderDrawRect(_renderer, &nextBlock);

	makeText("NEXT", "Market_Deco.ttf", 20, defaultTextColor, 30, 0);
}

void UserInterface::drawScore(unsigned long playerScore, int multiplier)
{
	makeText("COMBO", "armalite_rifle.ttf", 120, comboColor, 0, 0);
	makeText(std::to_string(playerScore), "Market_Deco.ttf", 60, defaultTextColor, 190, 75);
	makeText("x", "Market_Deco.ttf", 20, defaultTextColor, 80, 105);
	makeText(std::to_string(multiplier), "Market_Deco.ttf", 40, defaultTextColor, 100, 90);
}

void UserInterface::render()
{
	drawNextBlock();
	drawScore(1, 0);
}

void UserInterface::makeText(std::string text, std::string fontName, int fontSize, SDL_Color color, int xPos, int yPos)
{
	// Create Font
	TTF_Font* tempText = TTF_OpenFont(fontName.c_str(), fontSize);
	
	// Create Temp Surface
	SDL_Surface* tempSurface = TTF_RenderText_Blended(tempText, text.c_str(), color);

	// Get Text Dimensions
	SDL_Rect textDimensions;
	textDimensions.w = tempSurface->w;
	textDimensions.h = tempSurface->h;

	//Set Text Position
	SDL_Rect textPosition;
	textPosition.x = xPos;
	textPosition.y = yPos;
	textPosition.w = textDimensions.w;
	textPosition.h = textDimensions.h;

	// Convert to Texture
	SDL_Texture* tempTexture = SDL_CreateTextureFromSurface(_renderer, tempSurface);

	//Delete Temp Surface
	SDL_FreeSurface(tempSurface);

	SDL_RenderCopy(_renderer, tempTexture, NULL, &textPosition);

	SDL_Rect targetRect;
	targetRect.h = _nextBlockHeight;
	targetRect.w = _nextBlockWidth;
	targetRect.x = _nextBlockXPos;
	targetRect.y = _nextBlockYPos;

	SDL_SetRenderTarget(_renderer, NULL);
	SDL_RenderCopy(_renderer, nextBlockTexture, NULL, &targetRect);


}
