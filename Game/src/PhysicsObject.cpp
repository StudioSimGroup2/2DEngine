#include "PhysicsObject.h"

PhysicsObject::PhysicsObject(Device* dev, vec2f* position, char* name, Texture* tex) : Sprite(name, position, tex)
{
	mPhysics = new PhysicsComp();
	//mAI = new AI(position);
}

PhysicsObject::~PhysicsObject()
{
	delete mPhysics;
	//delete mAI;

	mPhysics = nullptr;
	//mAI = nullptr;
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