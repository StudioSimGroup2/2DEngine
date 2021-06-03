#include "Collision.h"

bool Collision::DoCollisionChecks(Engine::GameObject* object1, Engine::GameObject* object2)
{
	if (object1->GetComponent<Engine::ObjectCollisionComp>() != NULL && object2->GetComponent<Engine::ObjectCollisionComp>() != NULL)
	{
		if (BoxBoxCheck(object1, object2))
		{
			return true;
		}
	}

	if (object1->GetComponent<Engine::TilemapCollisionComp>() != NULL && object2->GetComponent<Engine::ObjectCollisionComp>() != NULL)
	{
		if (BoxTilemapCheck(object1, object2))
		{
			return true;
		}
	}

	if (object1->GetComponent<Engine::ObjectCollisionComp>() != NULL && object2->GetComponent<Engine::TilemapCollisionComp>() != NULL)
	{
		if (BoxTilemapCheck(object2, object1))
		{
			return true;
		}
	}

	if (object1->GetComponent<Engine::LineCollisionComp>() != NULL && object2->GetComponent<Engine::LineCollisionComp>() != NULL)
	{
		if (LineLineCheck(object2, object1))
		{
			return true;
		}
	}

	if (object1->GetComponent<Engine::ObjectCollisionComp>() != NULL && object2->GetComponent<Engine::LineCollisionComp>() != NULL)
	{
		if (LineBoxCheck(object2, object1))
		{
			return true;
		}
	}

	if (object1->GetComponent<Engine::LineCollisionComp>() != NULL && object2->GetComponent<Engine::ObjectCollisionComp>() != NULL)
	{
		if (LineBoxCheck(object1, object2))
		{
			return true;
		}
	}

	return false;
}

bool Collision::BoxBoxCheck(Engine::GameObject* object1, Engine::GameObject* object2)
{
	if (FindDistance(object1, object2) > object1->GetComponent<Engine::ObjectCollisionComp>()->GetBRange())
	{
		return false;
	}

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

bool Collision::BoxTilemapCheck(Engine::GameObject* tilemapBoxes, Engine::GameObject* object)
{

	bool colTrue;
	Box2D box1 = object->GetComponent<Engine::ObjectCollisionComp>()->GetColBox();
	std::vector<Box2D> boxes = tilemapBoxes->GetComponent<Engine::TilemapCollisionComp>()->GetColBoxes();

		for (Box2D box2 : boxes)
		{
			if (FindDistance(box1, box2) > object->GetComponent<Engine::ObjectCollisionComp>()->GetBRange())
			{
				colTrue = false;
				continue;
			}

			if (box1.GetPosition().x < box2.GetPosition().x + box2.GetSize().x &&
				box1.GetPosition().x + box1.GetSize().x > box2.GetPosition().x &&
				box1.GetPosition().y < box2.GetPosition().y + box2.GetSize().y &&
				box1.GetPosition().y + box1.GetSize().y > box2.GetPosition().y)
			{
				colTrue = true;
				break;
			}
			else
				colTrue = false;
		}

		return colTrue;
}

bool Collision::LineLineCheck(Engine::GameObject* line1, Engine::GameObject* line2)
{
	vec2f O1P1, O1P2, O2P1, O2P2;
	O1P1 = line1->GetComponent<Engine::LineCollisionComp>()->GetPoint1();
	O1P2 = line1->GetComponent<Engine::LineCollisionComp>()->GetPoint2();
	O2P1 = line2->GetComponent<Engine::LineCollisionComp>()->GetPoint1();
	O2P2 = line2->GetComponent<Engine::LineCollisionComp>()->GetPoint2();

	float uA, uB;
	uA = ((O2P2.x - O2P1.x) * (O1P1.y - O2P1.y) - (O2P2.y - O2P1.y) * (O1P1.x - O2P1.x)) / ((O2P2.y - O2P1.y) * (O1P2.x - O1P1.x) - (O2P2.x - O2P1.x) * (O1P2.y - O1P1.y));
	uB = ((O1P2.x - O1P1.x) * (O1P1.y - O2P1.y) - (O1P2.y - O1P1.y) * (O1P1.x - O2P1.x)) / ((O2P2.y - O2P1.y) * (O1P2.x - O1P1.x) - (O2P2.x - O2P1.x) * (O1P2.y - O1P1.y));

	if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1)
	{
		return true;
	}
	else
		return false;
}

bool Collision::LineLineCheck(vec2f point1, vec2f point2, vec2f point3, vec2f point4)
{
	double uA, uB;
	uA = ((point4.x - point3.x) * (point1.y - point3.y) - (point4.y - point3.y) * (point1.x - point3.x)) / ((point4.y - point3.y) * (point2.x - point1.x) - (point4.x - point3.x) * (point2.y - point1.y));
	uB = ((point2.x - point1.x) * (point1.y - point3.y) - (point2.y - point1.y) * (point1.x - point3.x)) / ((point4.y - point3.y) * (point2.x - point1.x) - (point4.x - point3.x) * (point2.y - point1.y));

	if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1)
	{
		return true;
	}
	else
		return false;
}

bool Collision::LineBoxCheck(Engine::GameObject* lineObj, Engine::GameObject* boxObj)
{
	//Set Line positions
	vec2f lineP1, lineP2;
	lineP1 = lineObj->GetComponent<Engine::LineCollisionComp>()->GetPoint1();
	lineP2 = lineObj->GetComponent<Engine::LineCollisionComp>()->GetPoint2();

	//Set Box positions
	vec2f boxPos, boxSize, boxUR, boxLL, boxLR;
	boxPos = boxObj->GetComponent<Engine::ObjectCollisionComp>()->GetColBox().GetPosition();
	boxSize = boxObj->GetComponent<Engine::ObjectCollisionComp>()->GetColBox().GetSize();

	//Box Remaining Corners (Upper left is Pos)
	boxUR.x = boxPos.x + boxSize.x;
	boxUR.y = boxPos.y;

	boxLL.x = boxPos.x;
	boxLL.y = boxPos.y + boxSize.y;

	boxLR.x = boxPos.x + boxSize.x;
	boxLR.y = boxPos.y + boxSize.y;


	bool left, up, right, down;
	left = LineLineCheck(lineP1, lineP2, boxPos, boxLL);
	up = LineLineCheck(lineP1, lineP2, boxPos, boxUR);
	right = LineLineCheck(lineP1, lineP2, boxUR, boxLR);
	down = LineLineCheck(lineP1, lineP2, boxLL, boxLR);

	if (left || right || up || down) 
	{
		return true;
	}
	else
		return false;
}

bool Collision::LineBoxCheck(vec2f point1, vec2f point2, Engine::GameObject* boxObj)
{
	//Set Box positions
	vec2f boxPos, boxSize, boxUR, boxLL, boxLR;
	boxPos = boxObj->GetComponent<Engine::ObjectCollisionComp>()->GetColBox().GetPosition();
	boxSize = boxObj->GetComponent<Engine::ObjectCollisionComp>()->GetColBox().GetSize();

	//Box Remaining Corners (Upper left is Pos)
	boxUR.x = boxPos.x + boxSize.x;
	boxUR.y = boxPos.y;

	boxLL.x = boxPos.x;
	boxLL.y = boxPos.y + boxSize.y;

	boxLR.x = boxPos.x + boxSize.x;
	boxLR.y = boxPos.y + boxSize.y;


	bool left, up, right, down;
	left = LineLineCheck(point1, point2, boxPos, boxLL);
	up = LineLineCheck(point1, point2, boxPos, boxUR);
	right = LineLineCheck(point1, point2, boxUR, boxLR);
	down = LineLineCheck(point1, point2, boxLL, boxLR);

	if (left || right || up || down)
	{
		return true;
	}
	else
		return false;
}

float Collision::FindDistance(Engine::GameObject* object1, Engine::GameObject* object2)
{
	float dy = object1->GetComponent<Engine::TransformComp>()->GetPosition().y - object2->GetComponent<Engine::TransformComp>()->GetPosition().y;
	float dx = object1->GetComponent<Engine::TransformComp>()->GetPosition().x - object2->GetComponent<Engine::TransformComp>()->GetPosition().x;

	return sqrt((dx * dx) + (dy * dy));
}

float Collision::FindDistance(Box2D box1, Box2D box2)
{
	float dy = box1.GetPosition().y - box2.GetPosition().y;
	float dx = box1.GetPosition().x - box2.GetPosition().x;

	return sqrt((dx * dx) + (dy * dy));
}

bool Collision::CheckBox(Box2D box1, Engine::GameObject* go)
{
	Box2D box2 = go->GetComponent<Engine::ObjectCollisionComp>()->GetColBox();

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

bool Collision::CheckCollision(Engine::GameObject* object1, Engine::GameObject* object2)
{
	if (object1 == object2)
		return false;

	if ((object1->GetComponent<Engine::ObjectCollisionComp>() != NULL && object1->GetComponent<Engine::ObjectCollisionComp>()->GetColToggle() == false) ||
		(object1->GetComponent<Engine::TilemapCollisionComp>() != NULL && object1->GetComponent<Engine::TilemapCollisionComp>()->GetColToggle() == false) ||
		(object1->GetComponent<Engine::LineCollisionComp>() != NULL && object1->GetComponent<Engine::LineCollisionComp>()->GetColToggle() == false))
	{
		return false;
	}
	else if ((object2->GetComponent<Engine::ObjectCollisionComp>() != NULL && object2->GetComponent<Engine::ObjectCollisionComp>()->GetColToggle() == false) ||
		(object2->GetComponent<Engine::TilemapCollisionComp>() != NULL && object2->GetComponent<Engine::TilemapCollisionComp>()->GetColToggle() == false) ||
		(object2->GetComponent<Engine::LineCollisionComp>() != NULL && object2->GetComponent<Engine::LineCollisionComp>()->GetColToggle() == false))
	{
		return false;
	}
	else
		if (DoCollisionChecks(object1, object2))
		{
			return true;
		}
		else
			return false;
}

bool Collision::CheckTrigger(Engine::GameObject* object1, Engine::GameObject* object2)
{
	if (object1 == object2)
		return false;

	if ((object1->GetComponent<Engine::ObjectCollisionComp>() != NULL && object1->GetComponent<Engine::ObjectCollisionComp>()->GetTrigger() == true) ||
		(object1->GetComponent<Engine::TilemapCollisionComp>() != NULL && object1->GetComponent<Engine::TilemapCollisionComp>()->GetTrigger() == true) ||
		(object1->GetComponent<Engine::LineCollisionComp>() != NULL && object1->GetComponent<Engine::LineCollisionComp>()->GetTrigger() == true))
	{
		if (DoCollisionChecks(object1, object2))
		{
			return true;
		}
		else
			return false;
	}

	if ((object2->GetComponent<Engine::ObjectCollisionComp>() != NULL && object2->GetComponent<Engine::ObjectCollisionComp>()->GetTrigger() == true) ||
		(object2->GetComponent<Engine::TilemapCollisionComp>() != NULL && object2->GetComponent<Engine::TilemapCollisionComp>()->GetTrigger() == true) ||
		(object2->GetComponent<Engine::LineCollisionComp>() != NULL && object2->GetComponent<Engine::LineCollisionComp>()->GetTrigger() == true))
	{
		if (DoCollisionChecks(object1, object2))
		{
			return true;
		}
		else
			return false;
	}
}

bool Collision::CheckLeft(Engine::GameObject* object, Box2D colBox)
{
	//Get Current and Old box data
	vec2f box1Pos, box1Size, oldBox1Pos;
	box1Pos = object->GetComponent<Engine::ObjectCollisionComp>()->GetColBox().GetPosition();
	box1Size = object->GetComponent<Engine::ObjectCollisionComp>()->GetColBox().GetSize();
	oldBox1Pos = object->GetComponent<Engine::PhysicsComp>()->GetPrevPos();

	//Get tilemap Box to compare against
	vec2f box2Pos, box2Size;
	box2Pos = colBox.GetPosition();
	box2Size = colBox.GetSize();

	//Prevent checking the floor when stood on floor
	if (box2Pos.y > ((box1Pos.y + box1Size.y) - 1.0f))
		return false;

	//Check left of object against right of tilebox
	if (oldBox1Pos.x >= (box2Pos.x + box2Size.x) && box1Pos.x < (box2Pos.x + box2Size.x))
		return true;
	else
		return false;
}

bool Collision::CheckRight(Engine::GameObject* object, Box2D colBox)
{
	//Get Current and Old box data
	vec2f box1Pos, box1Size, oldBox1Pos;
	box1Pos = object->GetComponent<Engine::ObjectCollisionComp>()->GetColBox().GetPosition();
	box1Size = object->GetComponent<Engine::ObjectCollisionComp>()->GetColBox().GetSize();
	oldBox1Pos = object->GetComponent<Engine::PhysicsComp>()->GetPrevPos();

	//Get tilemap Box to compare against
	vec2f box2Pos, box2Size;
	box2Pos = colBox.GetPosition();
	box2Size = colBox.GetSize();

	//Prevent checking the floor when stood on floor
	if (box2Pos.y > ((box1Pos.y + box1Size.y) - 1.0f))
		return false;

	//Check right of object against left of tilebox
	if ((oldBox1Pos.x + box1Size.x) < box2Pos.x && (box1Pos.x  + box1Size.x) >= box2Pos.x)
		return true;
	else
		return false;
}

bool Collision::CheckDown(Engine::GameObject* object, Box2D colBox)
{
	//Get Current and Old box data
	vec2f box1Pos, box1Size, oldBox1Pos;
	box1Pos = object->GetComponent<Engine::ObjectCollisionComp>()->GetColBox().GetPosition();
	box1Size = object->GetComponent<Engine::ObjectCollisionComp>()->GetColBox().GetSize();
	oldBox1Pos = object->GetComponent<Engine::PhysicsComp>()->GetPrevPos();

	//Get tilemap Box to compare against
	vec2f box2Pos, box2Size;
	box2Pos = colBox.GetPosition();
	box2Size = colBox.GetSize();

	if (oldBox1Pos.y == box1Pos.y)
	{
		return true;
	}

	//Check bottom of object against top of tilebox
	if ((oldBox1Pos.y + box1Size.y) < box2Pos.y && (box1Pos.y + box1Size.y) >= box2Pos.y)
		return true;
	else
		return false;
}

bool Collision::CheckUp(Engine::GameObject* object, Box2D colBox)
{
	//Get Current and Old box data
	vec2f box1Pos, box1Size, oldBox1Pos;
	box1Pos = object->GetComponent<Engine::ObjectCollisionComp>()->GetColBox().GetPosition();
	box1Size = object->GetComponent<Engine::ObjectCollisionComp>()->GetColBox().GetSize();
	oldBox1Pos = object->GetComponent<Engine::PhysicsComp>()->GetPrevPos();

	//Get tilemap Box to compare against
	vec2f box2Pos, box2Size;
	box2Pos = colBox.GetPosition();
	box2Size = colBox.GetSize();

	//Check top of object against bottom of tilebox
	if (oldBox1Pos.y >= (box2Pos.y + box2Size.y) && box1Pos.y < (box2Pos.y + box2Size.y))
		return true;
	else
		return false;
}