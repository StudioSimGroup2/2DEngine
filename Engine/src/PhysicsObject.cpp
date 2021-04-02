#include "PhysicsObject.h"


PhysicsObject::PhysicsObject(Device* dev, const std::string& name, const std::string& path, vec2f* position) : Sprite(dev, name, path, position)
{
	mPhysics = new Physics(position);
	mAI = new AI(position);
}

PhysicsObject::~PhysicsObject()
{
	delete mPhysics;
	delete mAI;

	mPhysics = nullptr;
	mAI = nullptr;
}

void PhysicsObject::Update(float deltaTime)
{
	mPhysics->Update(deltaTime);
	Sprite::Update(deltaTime);
}

void PhysicsObject::Render()
{
	Sprite::Draw();
}