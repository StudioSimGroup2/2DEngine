#include "LineCollisionComp.h"

Engine::LineCollisionComp::LineCollisionComp()
{
	Init();
}

Engine::LineCollisionComp::LineCollisionComp(GameObject* parent) : Component(parent)
{
	Init();
}

Engine::LineCollisionComp::~LineCollisionComp()
{
}

void Engine::LineCollisionComp::Init()
{
	point1 = (0.0f, 0.0f);
	point2 = (0.0f, 0.0f);
}

float Engine::LineCollisionComp::GetLength()
{
	float dx = point1.x / point2.x;
	float dy = point1.y / point2.y;

	return sqrt((dx * dx) + (dy * dy));
}



void Engine::LineCollisionComp::Update()
{

}

void Engine::LineCollisionComp::Render()
{

}
