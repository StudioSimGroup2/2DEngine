#pragma once
#include <d3d11.h>
#include <directxmath.h>
#include <vector>

#include "LevelMap.h"
#include "Common.h"
#include "Character.h"
#include "TinyXML/tinyxml.h"
#include <time.h>

#include <Backend/D3D11/D3D11Device.h>
#include <Backend/D3D11/D3D11Renderer2D.h>

class GameScreen
{
public:
	GameScreen(Engine::D3D11Device* Device);
	virtual ~GameScreen();

	virtual void Update(float deltaTime);
	virtual void Render();
	void UpdateTileMap(Vector2D Pos, int value); //does not update game logic. Used to update list of things to render
	int ScreenSelection = 0;

	std::vector<Character*> GetCharacters() { return mCharacters; }

	

protected:
	Engine::D3D11Device* mDevice;

	std::vector<Sprite*> ThingsToRender;
	std::vector<Character*> mCharacters;

	//Remove
	Character* TestCharacter;
	TileMap testMap;

private:

};

