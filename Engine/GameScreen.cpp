#include "GameScreen.h"

GameScreen::GameScreen(ID3D11DeviceContext* Context, ID3D11Device* Device)
{
	mContext = Context;
	mDevice = Device;
}

GameScreen::~GameScreen()
{
}

void GameScreen::Render()
{
}

void GameScreen::Update(float deltaTime)
{
}
