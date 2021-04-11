#include "GameObject.h"

Engine::GameObject::GameObject()
{
	std::cout << "Gaze into the the abyss:	       " << this << std::endl;
	InitTransformComponent();
}

Engine::GameObject::GameObject(GameObject* parent)
{
	mParent = parent; parent->AttachToParent(this);
	InitTransformComponent();
}

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

void Engine::GameObject::InitTransformComponent()
{
	AddComponent<TransformComp>(new TransformComp);
}
