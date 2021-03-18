#pragma once
#include <d3d11.h>
#include <directxmath.h>
#include <vector>

#include "LevelMap.h"
#include "Common.h"
#include "Character.h"
#include "TinyXML/tinyxml.h"
#include <time.h>

class GameScreen
{
public:
	GameScreen(ID3D11DeviceContext* Context, ID3D11Device* Device);
	virtual ~GameScreen();

	virtual void Update(float deltaTime);
	virtual void Render();
	int ScreenSelection = 0;

protected:
	ID3D11Device* mDevice;
	ID3D11DeviceContext* mContext;

private:

};

