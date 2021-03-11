#pragma once
#include <d3d11.h>
#include <directxmath.h>
#include <vector>
#include "Common.h"
#include "GameScreen.h"


class GameScreenManager
{
public:
	GameScreenManager(ID3D11DeviceContext* Context, SCREENS StartScreen);
	~GameScreenManager();

	void Render();
	void Update(float deltatime);
	
	void changeScreens(SCREENS Selection);
	bool Quit;

private:
	ID3D11DeviceContext* mContext;
	GameScreen* mCurrentScreen;
};

