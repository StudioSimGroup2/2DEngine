#include "ObjectCollisionComp.h"
#include "Entities\GameObject.h"

Engine::ObjectCollisionComp::ObjectCollisionComp()
{
	Init();
}

Engine::ObjectCollisionComp::ObjectCollisionComp(GameObject* parent) : Component(parent)
{
	Init();
}

Engine::ObjectCollisionComp::~ObjectCollisionComp()
{
}

void Engine::ObjectCollisionComp::Init()
{
	mType = "Object Collision";

	vec2f position = mParent->GetComponent<TransformComp>()->GetPosition();
	colBox.SetPosition(position);

	vec2f size = (32.0f, 32.0f);
	colBox.SetSize(size);
}

void Engine::ObjectCollisionComp::Update()
{
}

void Engine::ObjectCollisionComp::Render()
{
}
