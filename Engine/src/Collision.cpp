#include "Collision.h"

void Collision::Update(std::vector<Engine::GameObject*> gameObjects)
{
	for (Engine::GameObject* object1 : gameObjects)
	{
		for (Engine::GameObject* object2 : gameObjects)
		{
			Box2D box1 = object1->GetComponent<ObjectCollisionComp>()->GetColBox();
			Box2D box2 = object2->GetComponent<ObjectCollisionComp>()->GetColBox();

			if (box1.GetPosition().x < box2.GetPosition().x + box2.GetSize().x &&
				box1.GetPosition().x + box1.GetSize().x > box2.GetPosition().x &&
				box1.GetPosition().y < box2.GetPosition().y + box2.GetSize().y &&
				box1.GetPosition().y + box1.GetSize().y > box2.GetPosition().y) 
			{

			}

		}
	}
}
