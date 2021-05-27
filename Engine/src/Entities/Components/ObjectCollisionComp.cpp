#include "ObjectCollisionComp.h"
#include "Entities\GameObject.h"

Engine::ObjectCollisionComp::ObjectCollisionComp()
{
}

Engine::ObjectCollisionComp::~ObjectCollisionComp()
{
}

void Engine::ObjectCollisionComp::Init()
{
	mType = COMPONENT_COLBOX;
	vec2f position = mParent->GetComponent<TransformComp>()->GetPosition();
	colBox.SetPosition(position);

	vec2f size = (32.0f, 32.0f);
	colBox.SetSize(size);
}

void Engine::ObjectCollisionComp::Update()
{
	colBox.SetPosition(mParent->GetComponent<TransformComp>()->GetPosition());
}

void Engine::ObjectCollisionComp::Render()
{
}

void Engine::ObjectCollisionComp::Start()
{
}

void Engine::ObjectCollisionComp::InternalUpdate()
{
}

void Engine::ObjectCollisionComp::InternalRender()
{
}
