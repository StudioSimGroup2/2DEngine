#include "Collision.h"

bool Collision::Update(std::vector<Engine::GameObject*> gameObjects)
{
	for (Engine::GameObject* object1 : gameObjects)
	{
		for (Engine::GameObject* object2 : gameObjects)
		{
			if (object1->GetComponent<Engine::ObjectCollisionComp>() != NULL && object2->GetComponent<Engine::ObjectCollisionComp>() != NULL)
			{
				Box2D box1 = object1->GetComponent<Engine::ObjectCollisionComp>()->GetColBox();
				Box2D box2 = object2->GetComponent<Engine::ObjectCollisionComp>()->GetColBox();

				if (box1.GetPosition().x < box2.GetPosition().x + box2.GetSize().x &&
					box1.GetPosition().x + box1.GetSize().x > box2.GetPosition().x &&
					box1.GetPosition().y < box2.GetPosition().y + box2.GetSize().y &&
					box1.GetPosition().y + box1.GetSize().y > box2.GetPosition().y)
				{
					return true;
				}
				else
					return false;
			}

			if (object1->GetComponent<Engine::ObjectCollisionComp>() != NULL && object2->GetComponent<Engine::TilemapCollisionComp>() != NULL)
			{
				Box2D box1 = object1->GetComponent<Engine::ObjectCollisionComp>()->GetColBox();
				std::vector<Box2D> boxes = object2->GetComponent<Engine::TilemapCollisionComp>()->GetColBoxes();

				for (Box2D box2 : boxes)
				{
					if (box1.GetPosition().x < box2.GetPosition().x + box2.GetSize().x &&
						box1.GetPosition().x + box1.GetSize().x > box2.GetPosition().x&&
						box1.GetPosition().y < box2.GetPosition().y + box2.GetSize().y &&
						box1.GetPosition().y + box1.GetSize().y > box2.GetPosition().y)
					{
						return true;
					}
					else
						return false;
				}
				
			}

			if (object1->GetComponent<Engine::TilemapCollisionComp>() != NULL && object2->GetComponent<Engine::ObjectCollisionComp>() != NULL)
			{
				Box2D box2 = object2->GetComponent<Engine::ObjectCollisionComp>()->GetColBox();
				std::vector<Box2D> boxes = object1->GetComponent<Engine::TilemapCollisionComp>()->GetColBoxes();

				for (Box2D box1 : boxes)
				{
					if (box1.GetPosition().x < box2.GetPosition().x + box2.GetSize().x &&
						box1.GetPosition().x + box1.GetSize().x > box2.GetPosition().x&&
						box1.GetPosition().y < box2.GetPosition().y + box2.GetSize().y &&
						box1.GetPosition().y + box1.GetSize().y > box2.GetPosition().y)
					{
						return true;
					}
					else
						return false;
				}
			}

		}
	}
}
