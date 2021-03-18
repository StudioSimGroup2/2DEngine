#pragma once
#include <d3d11.h>
#include <directxmath.h>
#include <vector>
#include "Common.h"
#include "GameScreen.h"

#include <Backend/D3D11/D3D11Device.h>


class GameScreenManager
{
public:
	GameScreenManager(Engine::D3D11Device* device, SCREENS StartScreen);
	~GameScreenManager();

	void Render();
	void Update(float deltatime);
	
	void changeScreens(SCREENS Selection);
	GameScreen* getScreen() { return mCurrentScreen; };
	bool Quit = false;

private:
	Engine::D3D11Device* mDevice;
	GameScreen* mCurrentScreen;
};

