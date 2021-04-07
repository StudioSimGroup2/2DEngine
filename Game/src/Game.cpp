#include <Engine.h>

#include "GameScreenManager.h"

class GameLayer : public Engine::Layer
{
public:
	GameLayer()
	{
		mGameScreenManager = new GameScreenManager(nullptr, SCREEN_TEST);
	}

	virtual ~GameLayer() = default;

	virtual void Render() override
	{
		if (mGameScreenManager->getScreen())
			mGameScreenManager->Render();
	}

	virtual void Update() override
	{
		float fps = 1.0f / 60.0f; // This is temporary till we have a timer class 

		if (mGameScreenManager->getScreen())
			mGameScreenManager->Update(fps);
	}

private:
	GameScreenManager* mGameScreenManager;
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