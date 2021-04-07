#pragma once
#include <d3d11.h>
#include <directxmath.h>
#include <vector>
#include "Common.h"
#include "GameScreen.h"

#include <Engine/Renderer/Device.h>


class GameScreenManager
{
public:
	GameScreenManager(Engine::Device* device, SCREENS StartScreen);
	~GameScreenManager();

	void Render();
	void Update(float deltatime);

	void changeScreens(SCREENS Selection);
	GameScreen* getScreen() { return mCurrentScreen; };
	bool Quit = false;

private:
	Engine::Device* mDevice;
	GameScreen* mCurrentScreen;
};

