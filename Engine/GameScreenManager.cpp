#include "GameScreenManager.h"

GameScreenManager::GameScreenManager(ID3D11DeviceContext* Context, SCREENS StartScreen)
{
	mContext = Context;
	mCurrentScreen = NULL;
	changeScreens(StartScreen);
}

GameScreenManager::~GameScreenManager()
{
}

void GameScreenManager::Render()
{
}

void GameScreenManager::Update(float deltatime)
{
}

void GameScreenManager::changeScreens(SCREENS Selection)
{
	if (mCurrentScreen != NULL)
	{
		delete mCurrentScreen;
	}

	GameScreen* TempScreen;
	TempScreen = new GameScreen(mContext);

	mCurrentScreen = (GameScreen*)TempScreen;
}
