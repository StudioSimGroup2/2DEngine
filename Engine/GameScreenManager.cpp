#include "GameScreenManager.h"
#include "GameScreenTest.h"

GameScreenManager::GameScreenManager(ID3D11DeviceContext* Context, ID3D11Device* Device, SCREENS StartScreen)
{
	mDevice = Device;
	mContext = Context;
	mCurrentScreen = NULL;
	changeScreens(StartScreen);
}

GameScreenManager::~GameScreenManager()
{
	//delete memeber variables

}

void GameScreenManager::Render()
{
	mCurrentScreen->Render();
}

void GameScreenManager::Update(float deltatime)
{
	mCurrentScreen->Update(deltatime);
}

void GameScreenManager::changeScreens(SCREENS Selection)
{
	if (mCurrentScreen != NULL)
	{
		delete mCurrentScreen;
		mCurrentScreen = nullptr;
	}

	GameScreen* NewScreen;

	switch (Selection)
	{
	case SCREEN_TEST:
		NewScreen = new GameScreenTest(mContext, mDevice);
		mCurrentScreen = (GameScreen*)NewScreen;
		break;
	case SCREEN_LEVEL1:
		break;
	default:
		break;
	}
}
