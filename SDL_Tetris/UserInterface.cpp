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
	_blockTitleFont = TTF_OpenFont("yukarimobil.ttf", 30);
	_defaultFont = TTF_OpenFont("yukarimobil.ttf", 20);
	_levelNumberFont = TTF_OpenFont("yukarimobil.ttf", 100);
	_scoreFont = TTF_OpenFont("yukarimobil.ttf", 60);
	_titleFont = TTF_OpenFont("yukarimobil.ttf", 100);
}

UserInterface::~UserInterface()
{
	TTF_CloseFont(_blockTitleFont);
	TTF_CloseFont(_levelNumberFont);
	TTF_CloseFont(_scoreFont);
	TTF_CloseFont(_titleFont);
	_blockTitleFont = nullptr;
	_levelNumberFont = nullptr;
	_scoreFont = nullptr;
	_titleFont = nullptr;
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

	if (type == typeid(I_Block)) {
		I_Block iBlock(_renderer, _gameBoard, 390,155);
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
		O_Block oBlock(_renderer, _gameBoard, 390, 160);
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

void UserInterface::drawLevelFrame(const unsigned int &level)
{
	// Create Level Text
	std::string levelString = std::to_string(level);
	SDL_Surface* levelText = TTF_RenderText_Blended(_levelNumberFont, levelString.c_str(), _defaultColor);
	_levelTexture = SDL_CreateTextureFromSurface(_renderer, levelText);

	SDL_Surface* levelTitleText = TTF_RenderText_Blended(_blockTitleFont, "Level", _defaultColor);
	_levelTitleTexture = SDL_CreateTextureFromSurface(_renderer, levelTitleText);

	int levelWidth = levelText->w;
	int levelHeight = levelText->h;

	int levelTitleWidth = levelTitleText->w;
	int levelTitleHeight = levelTitleText->h;

	SDL_FreeSurface(levelText);
	SDL_FreeSurface(levelTitleText);

	SDL_Rect levelTextRect;
	levelTextRect.w = levelWidth;
	levelTextRect.h = levelHeight;
	levelTextRect.x = 0;
	levelTextRect.y = 0;

	SDL_Rect targetRect;
	targetRect.w = levelWidth;
	targetRect.h = levelHeight;
	targetRect.x = 450;
	targetRect.y = 475;

	SDL_Rect levelTitleTextRect;
	levelTitleTextRect.w = levelTitleWidth;
	levelTitleTextRect.h = levelTitleHeight;
	levelTitleTextRect.x = 0;
	levelTitleTextRect.y = 0;

	SDL_Rect targetRect2;
	targetRect2.w = levelTitleWidth;
	targetRect2.h = levelTitleHeight;
	targetRect2.x = 420;
	targetRect2.y = 455;

	SDL_RenderCopy(_renderer, _levelTexture, &levelTextRect, &targetRect);
	SDL_RenderCopy(_renderer, _levelTitleTexture, &levelTitleTextRect, &targetRect2);

	SDL_DestroyTexture(_levelTexture);
	SDL_DestroyTexture(_levelTitleTexture);
}

void UserInterface::drawLinesFrame(const unsigned int &linesDeleted)
{
	// Create Lines Text
	std::string linesDeletedString = std::to_string(linesDeleted);
	SDL_Surface* linesText = TTF_RenderText_Blended(_defaultFont, linesDeletedString.c_str(), _defaultColor);
	_linesTexture = SDL_CreateTextureFromSurface(_renderer, linesText);

	SDL_Surface* linesTitleText = TTF_RenderText_Blended(_defaultFont, "Lines Deleted", _defaultColor);
	_linesTitleTexture = SDL_CreateTextureFromSurface(_renderer, linesTitleText);

	int linesWidth = linesText->w;
	int linesHeight= linesText->h;

	int linesTitleWidth = linesTitleText->w;
	int linesTitleHeight = linesTitleText->h;

	SDL_FreeSurface(linesText);
	SDL_FreeSurface(linesTitleText);

	SDL_Rect linesTextRect;
	linesTextRect.w = linesWidth;
	linesTextRect.h = linesHeight;
	linesTextRect.x = 0;
	linesTextRect.y = 0;

	SDL_Rect targetRect;
	targetRect.w = linesWidth;
	targetRect.h = linesHeight;
	targetRect.x = 500;
	targetRect.y = 270;

	SDL_Rect linesTitleTextRect;
	linesTitleTextRect.w = linesTitleWidth;
	linesTitleTextRect.h = linesTitleHeight;
	linesTitleTextRect.x = 0;
	linesTitleTextRect.y = 0;

	SDL_Rect targetRect2;
	targetRect2.w = linesTitleWidth;
	targetRect2.h = linesTitleHeight;
	targetRect2.x = 400;
	targetRect2.y = 250;

	SDL_RenderCopy(_renderer, _linesTexture, &linesTextRect, &targetRect);
	SDL_RenderCopy(_renderer, _linesTitleTexture, &linesTitleTextRect, &targetRect2);

	SDL_DestroyTexture(_linesTexture);
	SDL_DestroyTexture(_levelTitleTexture);
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

void UserInterface::render(unsigned long &playerScore, int &multiplier, unsigned int &level, unsigned int &linesDeleted, const type_info &type)
{
	drawTitle();
	drawScore(playerScore);
	drawBlockFrame(type);
	drawLevelFrame(level);
	drawLinesFrame(linesDeleted);
}
