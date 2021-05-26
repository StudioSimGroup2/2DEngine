#include "TransformComp.h"

Engine::TransformComp::TransformComp()
{
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
	mType = 0;
}

void Engine::TransformComp::Start()
{
}

void Engine::TransformComp::InternalUpdate()
{
}

void Engine::TransformComp::InternalRender()
{
}
