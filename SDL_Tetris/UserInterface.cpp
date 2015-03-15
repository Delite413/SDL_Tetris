#include "UserInterface.h"
#include "I_Block.h"
#include "J_Block.h"
#include "L_Block.h"
#include "O_Block.h"
#include "S_Block.h"
#include "T_Block.h"
#include "Z_Block.h"


UserInterface::UserInterface(SDL_Renderer* _renderer, Board* _gameBoard) : _renderer(_renderer), _gameBoard(_gameBoard), _scoreFont(nullptr)
{
	// Set Default Text Color ( White )
	_defaultColor.r = 255;
	_defaultColor.g = 255;
	_defaultColor.b = 255;
	_defaultColor.a = 255;

	// Set Combo Text Color ( Dark Red )
	_comboColor.r = 100;
	_comboColor.g = 0;
	_comboColor.b = 0;
	_comboColor.a = 0;

	// Set Title Colors 
	_titleColor.r = 60;
	_titleColor.g = 60;
	_titleColor.b = 60;
	_titleColor.a = 255;

	// Fonts / Sizes
	_scoreFont = TTF_OpenFont("yukarimobil.ttf", 60);
	_titleFont = TTF_OpenFont("yukarimobil.ttf", 100);
}

UserInterface::~UserInterface()
{
	TTF_CloseFont(_scoreFont);
	_scoreFont = nullptr;
}

void UserInterface::drawBlockFrame(const type_info &type)
{
	SDL_Rect insideBox;
	insideBox.w = 100;
	insideBox.h = 100;
	insideBox.x = 400;
	insideBox.y = 150;

	SDL_SetRenderDrawColor(_renderer, 150, 150, 150, 255);
	SDL_RenderDrawRect(_renderer, &insideBox);

	std::cout << type.name() << std::endl;

	if (type == typeid(I_Block)) {
		I_Block iBlock(_renderer, _gameBoard, 400,155);
		iBlock.render();
	}
	else if (type == typeid(J_Block)) {
		J_Block jBlock(_renderer, _gameBoard, 400, 155);
		jBlock.render();
	}
	else if (type == typeid(L_Block)) {
		L_Block lBlock(_renderer, _gameBoard, 400, 155);
		lBlock.render();
	}
	else if (type == typeid(O_Block)) {
		O_Block oBlock(_renderer, _gameBoard, 400, 155);
		oBlock.render();
	}
	else if (type == typeid(S_Block)) {
		S_Block sBlock(_renderer, _gameBoard, 400, 155);
		sBlock.render();
	}
	else if (type == typeid(T_Block)) {
		T_Block tBlock(_renderer, _gameBoard, 400, 155);
		tBlock.render();
	}
	else if (type == typeid(Z_Block)) {
		Z_Block zBlock(_renderer, _gameBoard, 400, 155);
		zBlock.render();
	}
	
}

void UserInterface::drawScore(unsigned long &playerScore)
{
	// Create Score Text
	std::string playerScoreString = std::to_string(playerScore);
	SDL_Surface* scoreText = TTF_RenderText_Blended(_scoreFont, playerScoreString.c_str(), _defaultColor);
	_scoreTexture = SDL_CreateTextureFromSurface(_renderer, scoreText);

	int scoreWidth = scoreText->w;
	int scoreHeight = scoreText->h;

	SDL_FreeSurface(scoreText);

	SDL_Rect scoreTextRect;
	scoreTextRect.w = scoreWidth;
	scoreTextRect.h = scoreHeight;
	scoreTextRect.x = 0;
	scoreTextRect.y = 0;

	SDL_Rect targetRect;
	targetRect.w = scoreWidth;
	targetRect.h = scoreHeight;
	targetRect.x = 275;
	targetRect.y = 75;

	SDL_RenderCopy(_renderer, _scoreTexture, &scoreTextRect, &targetRect);
	SDL_DestroyTexture(_scoreTexture);
}

void UserInterface::drawTitle()
{
	// Draw Title Text
	SDL_Surface* titleText = TTF_RenderText_Blended(_titleFont, "SDL_TETRIS", _titleColor);
	_titleTexture = SDL_CreateTextureFromSurface(_renderer, titleText);

	int titleWidth = titleText->w;
	int titleHeight = titleText->h;

	SDL_FreeSurface(titleText);

	SDL_Rect titleTextRect;
	titleTextRect.w = titleWidth;
	titleTextRect.h = titleHeight;
	titleTextRect.x = 0;
	titleTextRect.y = 0;

	SDL_Rect targetRect;
	targetRect.w = titleWidth;
	targetRect.h = titleHeight;
	targetRect.x = -135;
	targetRect.y = 290;

	SDL_RenderCopyEx(_renderer, _titleTexture, &titleTextRect, &targetRect, 270, NULL, SDL_FLIP_NONE);
	SDL_DestroyTexture(_titleTexture);
}

void UserInterface::render(unsigned long &playerScore, int &multiplier, unsigned int &linesDeleted, const type_info &type)
{
	drawTitle();
	drawScore(playerScore);
	drawBlockFrame(type);
}
