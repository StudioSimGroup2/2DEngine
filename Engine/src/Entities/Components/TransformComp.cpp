#include "TransformComp.h"

Engine::TransformComp::TransformComp() : Component()
{
	Init();
}

Engine::TransformComp::TransformComp(GameObject* parent) : Component(parent)
{
	Init();
}

Engine::TransformComp::~TransformComp()
{
	mParent = nullptr;
}

void Engine::TransformComp::Update()
{
}

void Engine::TransformComp::Render()
{
}

void Engine::TransformComp::Init()
{
	mPosition = vec2f(0);
	mScale = vec2f(1);
	mRotation = vec2f(0);
	mType = "Transform";
}
