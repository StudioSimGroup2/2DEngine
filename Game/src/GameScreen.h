#pragma once
#include <vector>

#include "Utils/LevelMap.h"
#include "Common.h"
#include "Character.h"
#include "../../TinyXML/src/tinyxml.h"
#include <time.h>

class GameScreen
{
public:
	GameScreen(Engine::Device* Device);
	virtual ~GameScreen();

	virtual void Update(float deltaTime);
	virtual void Render();
	int ScreenSelection = 0;

protected:
	Engine::Device* mDevice;

private:

};

