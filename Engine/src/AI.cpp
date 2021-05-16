#include "AI.h"


AI::AI(vec2f* position)
{
	charPos = position;
}

AI::~AI()
{

}

void AI::Update(float deltaTime)
{
	switch (movementState)
	{
	case(IDLE):
		{
			
		break;
		}
	case(WANDER):
		{
		srand(float(deltaTime));
		CreatePath(AllNodes[rand() % AllNodes.size()]->ID);
		break;
		}
	case(PERSUE):
		{
			
		break;
		}
	}

}

vector<Vector2D> AI::GetWaypointPositions()
{
	vector<Vector2D> waypointPos;

	for (int i = 0; i < AllNodes.size(); i++)
	{
		waypointPos.push_back(AllNodes[i]->pos);
	}

	return waypointPos;
}

Node AI::FindStartPoint()
{
	float sDist = 9999;
	Node closestWaypoint;

	for each (Node* node in AllNodes)
	{
		float dist = GetPythag(Vector2D(charPos->x, charPos->y), node->pos);
		if (sDist > dist)
		{
			sDist = dist;
			closestWaypoint.ID = node->ID;
			closestWaypoint.parentID = node->parentID;
			closestWaypoint.pos = node->pos;
			closestWaypoint.hCost = node->hCost;
			closestWaypoint.gCost = node->gCost;
			closestWaypoint.fCost = node->fCost;
		}
	}

	return closestWaypoint;
}

Node AI::FindNodeWithID(int ID)
{
	for each (Node* node in AllNodes)
	{
		if (node->ID == ID)
		{
			Node tempNode;
			tempNode.ID = node->ID;
			tempNode.parentID = node->parentID;
			tempNode.pos = node->pos;
			tempNode.hCost = node->hCost;
			tempNode.gCost = node->gCost;
			tempNode.fCost = node->fCost;
			return tempNode;
		}
	}
}

void AI::CreatePath(int endWaypointID)
{
	//Find the end waypoint
	Node endWaypoint = FindNodeWithID(endWaypointID);

	//Clear path positions
	pathPos.clear();

	//Find nearest waypoint to current position, add it as the first position to navigate to
	bool pathMade = false;
	Node closestStart = FindStartPoint();
	pathPos.push_back(closestStart.pos);

	//Create a local starting node to find a path with
	Node start;
	start.parentID = -1;
	start.pos = closestStart.pos;
	start.gCost = 100000;
	start.hCost = GetPythag(start.pos, Vector2D(charPos->x, charPos->y));
	start.fCost = start.gCost + start.hCost;


	//Create two lists of nodes to calculate the path
	vector<Node> openWaypoints;
	vector<Node> closedWaypoints;

	Node current = start;

	openWaypoints.push_back(start);

	while (!pathMade)
	{
		for each (Node point in openWaypoints)
		{
			if (point.fCost < current.fCost)
				current = point;
		}

		for (int i = 0; i < openWaypoints.size(); i++)
		{
			if (openWaypoints[i].ID == current.ID)
			{
				openWaypoints.erase(openWaypoints.begin() + i);
				closedWaypoints.push_back(current);
			}
		}

		if (current.ID == endWaypoint.ID)
		{
			pathMade = true;
			break;
		}

		for (int i = 0; i < size(current.GetConnectedIDs()); i++)
		{
			Node neighbour = FindNodeWithID(current.GetConnectedIDs()[i]);
			if (NodeInList(neighbour, closedWaypoints))
			{
				continue;
			}

			if (neighbour.fCost > current.fCost + (GetPythag(neighbour.pos, current.pos)) || !NodeInList(neighbour, openWaypoints))
			{
				neighbour.gCost = GetPythag(neighbour.pos, current.pos);
				neighbour.hCost = GetPythag(neighbour.pos, current.pos);
				neighbour.fCost = neighbour.gCost + neighbour.hCost;
				neighbour.parentID = current.ID;

				UpdateAllNodes(neighbour);

				if (!NodeInList(neighbour, openWaypoints))
				{
					openWaypoints.push_back(neighbour);
				}

			}
		}
	}

	vector<Node> CompletePath;
	Node pathNode = current;
	while (pathNode.ID != start.ID)
	{
		CompletePath.push_back(pathNode);
		pathNode = FindNodeWithID(pathNode.parentID);
	}

	for (int i = 0; i < size(CompletePath); i++)
	{
		pathPos.push_back(CompletePath[CompletePath.size() - (1 + i)].pos);
	}

	pathPos.push_back(FindNodeWithID(endWaypointID).pos);

}

bool AI::NodeInList(Node node, vector<Node> list)
{

	for (int i = 0; i < size(list); i++)
	{
		if (node.ID == list[i].ID)
		{
			return true;
		}
	}

	return false;
}

void AI::UpdateAllNodes(Node node)
{
	for (int i = 0; i < size(AllNodes); i++)
	{
		if (AllNodes[i]->ID == node.ID)
		{
			Node* tempNode = new Node();
			tempNode->ID = node.ID;
			tempNode->parentID = node.parentID;
			tempNode->connectedIDs = node.connectedIDs;
			tempNode->pos = node.pos;
			tempNode->hCost = node.hCost;
			tempNode->gCost = node.gCost;
			tempNode->fCost = node.hCost;
			AllNodes[i] = tempNode;
		}
	}
}

void AI::NavigatePath()
{

}

float AI::GetPythag(Vector2D vec1, Vector2D vec2)
{
	float difX = vec1.X - vec2.X;
	float difY = vec1.Y - vec2.Y;

	float X2 = difX * difX;
	float Y2 = difY * difY;

	float pythag = sqrt(X2 + Y2);
	return pythag;
}
