#include "PhysicsObject.h"


PhysicsObject::PhysicsObject(ID3D11Device* device, const wchar_t* name, Vector2D Position) : Sprite(device, name, Position)
{
	mPhysics = new Physics();
}

PhysicsObject::~PhysicsObject()
{
	delete mPhysics;
	mPhysics = nullptr;
}

void PhysicsObject::Update(float deltaTime)
{
	mPhysics->Update(deltaTime);
	Sprite::Update(deltaTime);
}

void PhysicsObject::Render(ID3D11DeviceContext* devCon)
{
	Sprite::Render(devCon);
}