#include "GameScreenManager.h"
#include "GameScreenTest.h"

GameScreenManager::GameScreenManager(Engine::Device* device, SCREENS StartScreen)
{
	mDevice = device;

	mCurrentScreen = NULL;
	changeScreens(StartScreen);
}

GameScreenManager::~GameScreenManager()
{
	/*delete memeber variables*/
	delete mCurrentScreen;
	mCurrentScreen = nullptr;
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
		NewScreen = new GameScreenTest(mDevice);
		mCurrentScreen = (GameScreen*)NewScreen;
		break;
	case SCREEN_LEVEL1:
		break;
	default:
		break;
	}
}
