#include "AI.h"

AI::AI(Device* dev, const std::string& name, const std::string& path, vec2f* position) : Character(dev, name, path, position)
{

}

AI::~AI()
{

}


void AI::FindStartPoint()
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
		srand(deltaTime);
		CreatePath(nodes[rand() % nodes.size()].waypoint.ID);
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

	for (int i = 0; i < nodes.size(); i++)
	{
		waypointPos.push_back(nodes[i].waypoint.pos);
	}

	return waypointPos;
}

void AI::CreatePath(int endNodeID)
{
	pathPos.clear();

	bool pathMade = false;
	Waypoint* closestStart = FindStartPoint();
	Waypoint* closestEnd = FindNearestToPoint(point);
	pathPos.push_back(closestStart->GetPosition());

	Node start;
	start.parentID = -1;
	start.waypoint = closestStart;
	start.gCost = 100000;
	start.hCost = GetPythag(start.waypoint->GetPosition(), GetCentralPosition());
	start.fCost = start.gCost + start.hCost;



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
			if (openWaypoints[i].waypoint->GetID() == current.waypoint->GetID())
			{
				openWaypoints.erase(openWaypoints.begin() + i);
				closedWaypoints.push_back(current);
			}
		}

		if (current.waypoint == closestEnd)
		{
			pathMade = true;
			break;
		}

		for (int i = 0; i < size(current.waypoint->GetConnectedWaypointIDs()); i++)
		{
			Node neighbour = FindNodeWithID(current.waypoint->GetConnectedWaypointIDs()[i]);
			if (NodeInList(neighbour, closedWaypoints))
			{
				continue;
			}

			if (neighbour.fCost > current.fCost + (GetPythag(neighbour.waypoint->GetPosition(), current.waypoint->GetPosition())) || !NodeInList(neighbour, openWaypoints))
			{
				neighbour.gCost = GetPythag(neighbour.waypoint->GetPosition(), current.waypoint->GetPosition());
				neighbour.hCost = GetPythag(neighbour.waypoint->GetPosition(), closestEnd->GetPosition());
				neighbour.fCost = neighbour.gCost + neighbour.hCost;
				neighbour.parentID = current.waypoint->GetID();

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
	while (pathNode.waypoint != start.waypoint)
	{
		CompletePath.push_back(pathNode);
		pathNode = FindNodeWithID(pathNode.parentID);
	}

	for (int i = 0; i < size(CompletePath); i++)
	{
		navigationPoints.push_back(CompletePath[CompletePath.size() - (1 + i)].waypoint->GetPosition());
	}

	navigationPoints.push_back(point);
}

void AI::NavigatePath()
{

}
