#include "GameObject.h"

Engine::GameObject::GameObject()
{
	InitTransformComponent();
}

Engine::GameObject::GameObject(GameObject* parent)
{
	mParent = parent; parent->AttachToParent(this);
	InitTransformComponent();
}

Engine::GameObject::~GameObject()
{
	for (Component* c : mComponents)
	{
		delete c;
		c = nullptr;
	}
	mComponents.shrink_to_fit();

	//TODO Add children back to the scene hierachy 
	for (GameObject* child : mChildren)
	{
		child->SetParent(nullptr);
		child = nullptr;
	}
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
