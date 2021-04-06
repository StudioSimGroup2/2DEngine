#pragma once
#include <d3d11.h>
#include <directxmath.h>
#include <vector>
#include <time.h>

#include "Common.h"
#include "TinyXML/tinyxml.h"
#include "LevelMap.h"
#include "Character.h"
#include "ParticalSystem.h"



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

	std::vector<Sprite*> ThingsToRender; //List of all characters in the given scenes
	std::vector<Character*> mCharacters;
	std::vector<ParticleSystem*> mParticleSystems;
private:

};

