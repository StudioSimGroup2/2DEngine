#pragma once
#include <d3d11.h>
#include <directxmath.h>
#include <vector>

class GameScreen
{
	GameScreen(ID3D11DeviceContext* Context);
	~GameScreen();

	virtual void Render();
	virtual void Update(float deltaTime);
	int ScreenSelection;

private:

};

