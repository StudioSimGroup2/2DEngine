#include "PhysicsObject.h"

PhysicsObject::PhysicsObject(char* name, vec2f* position, Texture* tex) : Sprite(name, position, tex)
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