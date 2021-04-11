#include <Engine.h>

#include "GameScreenManager.h"
#include "SceneManager.h"
#include "Scene.h"

class GameLayer : public Engine::Layer
{
public:
	GameLayer()
	{
		SceneManager::GetInstance()->LoadScene();
	}

	virtual ~GameLayer()
	{
	}

	virtual void Render() override
	{
		SceneManager::GetInstance()->RenderScene();
	}

	virtual void Update() override
	{
		SceneManager::GetInstance()->UpdateScene();
	}

private:
};

class Game : public Engine::Application
{
public:
	Game()
	{
		AddLayer(new GameLayer());
	}

	~Game()
	{

	}
};

Engine::Application* Engine::CreateApplication()
{
	return new Game();
}