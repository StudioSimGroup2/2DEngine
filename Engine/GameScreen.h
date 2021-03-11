#pragma once
#include <d3d11.h>
#include <directxmath.h>
#include <vector>

class GameScreen
{
public:
	GameScreen(ID3D11DeviceContext* Context, ID3D11Device* Device);
	~GameScreen();

	virtual void Update(float deltaTime);
	virtual void Render();
	int ScreenSelection = 0;

protected:
	ID3D11Device* mDevice;
	ID3D11DeviceContext* mContext;

private:

};

