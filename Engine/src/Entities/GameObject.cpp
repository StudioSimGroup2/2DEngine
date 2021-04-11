#include "GameObject.h"

void Engine::GameObject::Start()
{
}

void Engine::GameObject::Update()
{
	if (!mStatus)
		return;

	for (Component* c : mComponents)
		c->Update();
}

void Engine::GameObject::FixedUpdate()
{
}

void Engine::GameObject::Render()
{
	if (!mStatus)
		return;

	for (Component* c : mComponents)
		c->Render();
}

void Engine::GameObject::OnEnable()
{
}

void Engine::GameObject::OnDisable()
{
}
