#include "Arena.h"

Arena::Arena()
{
	limit_box.setPosition(130, 100);
	limit_box.setSize(sf::Vector2f(1700, 800));
	textureBackImag.loadFromFile("pic/newarena.png");
	spriteBackGroundImage.setTexture(textureBackImag);
	spriteBackGroundImage.scale(2, 1.3);
	/*direction[0] = sf::Vector2f(0, step);
	direction[1] = sf::Vector2f(step, step);
	direction[2] = sf::Vector2f(step, 0);
	direction[3] = sf::Vector2f(step, -step);
	direction[4] = sf::Vector2f(0, -step);
	direction[5] = sf::Vector2f(-step, -step);
	direction[6] = sf::Vector2f(-step,0);
	direction[7] = sf::Vector2f(-step, step);*/
	direction.push_back(sf::Vector2f(0, step));
	direction.push_back(sf::Vector2f(step, 0));
	direction.push_back(sf::Vector2f(0, -step));
	direction.push_back(sf::Vector2f(-step, 0));
	direction.push_back(sf::Vector2f(-step, step));
	direction.push_back(sf::Vector2f(-step, -step));
	direction.push_back(sf::Vector2f(step, -step));
	direction.push_back(sf::Vector2f(step, step));

	for (int i = 0; i < noOfBlocks; i++)
	{
		blocks[i].setFillColor(sf::Color::Transparent);
		blocks[i].setSize(sizes[i]);
		blocks[i].setPosition(positions[i]);
	}

	startingNode = createNode(sf::Vector2f(100, 100));
	node_object.push_back(startingNode);
	expandNode(startingNode);
}

void Arena::draw(sf::RenderWindow& window)
{
	window.draw(spriteBackGroundImage);
	/*if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		mp.x = sf::Mouse::getPosition().x;
		mp.y = sf::Mouse::getPosition().y;
		std::cout << "(" << mp.x << "," << mp.y << ")" << std::endl;
	}*/

	if (showNode) {
		for (const auto node : node_object)
		{
			node->draw(window);
		}
	}
	if (showEdge) {
		for (const auto node : node_object)
		{
			for (const auto neighbour : node->neighbours)
			{
				if (getNodeById(neighbour))
				{
					sf::Vertex line[]{
							sf::Vertex(node->getPosition()),
							sf::Vertex(getNodeById(neighbour)->getPosition())
					};
					window.draw(line, 2, sf::Lines);
				}
			}
		}
	}

	if (currentPath.size() > 2 && showPath)
	{
		for (int i = 0; i < currentPath.size() - 1; i++)
		{
			sf::Vertex line[]
			{
				sf::Vertex(currentPath[i]->getPosition()),
				sf::Vertex(currentPath[i + 1]->getPosition())
			};
			window.draw(line, 2, sf::Lines);
		}
	}
}

bool Arena::is_freespace(sf::Vector2f position)
{
	if (!limit_box.getGlobalBounds().contains(position))
	{
		return false;
	}
	for (const auto block : blocks)
	{
		if (block.getGlobalBounds().contains(position))
		{
			return false;
		}
	}
	return true;
}

bool Arena::nodeExists(sf::Vector2f position)
{
	for (auto node : node_object)
	{
		if (node->getPosition() == position)
		{
			return true;
		}
	}
	return false;
}

Node* Arena::getnode(sf::Vector2f position)
{
	for (auto node : node_object)
	{
		if (node->getPosition() == position)
		{
			return node;
		}
	}
	return NULL;
}

void Arena::expandNode(Node* self)
{
	sf::Vector2f projectedCoord;
	Node* neighbour, * newNode;
	for (int i = 0; i < direction.size(); i++)
	{
		projectedCoord = self->getPosition() + direction[i];
			if (nodeExists(projectedCoord))
			{
				neighbour = getnode(projectedCoord);
				if (neighbour)
				{
					neighbour->add_to_neighbours(self->getId());
					self->add_to_neighbours(neighbour->getId());
				}
			}
			else
			{
				if (is_freespace(projectedCoord))
				{
					newNode = createNode(projectedCoord);
					node_object.push_back(newNode);
					expandNode(newNode);
				}
			}
		
	}
}

Node* Arena::createNode(sf::Vector2f position)
{
	Node* node = new Node(position);
	node->body.setOutlineColor(sf::Color::Blue);
	node->body.setOutlineThickness(1);
	node->body.setRadius(2);
	return node;
}

Node* Arena::getNodeById(int id)
{
	for (auto node : node_object)
	{
		if (node->getId() == id)
		{
			return node;
		}
	}
	return NULL;
}

Node* Arena::getNearestNode(sf::Vector2f playerPosition)
{
	float shortDistance;
	Node* nearestNode = node_object[0];
	shortDistance = pow(playerPosition.x - node_object[0]->getPosition().x, 2) + pow(playerPosition.y - node_object[0]->getPosition().y, 2);
	for (const auto node : node_object)
	{
		//if (isInLineOfSight(node->getPosition(), playerPosition)) {
			if (shortDistance > (pow(playerPosition.x - node->getPosition().x, 2) + pow(playerPosition.y - node->getPosition().y, 2)))
			{
				shortDistance = pow(playerPosition.x - node->getPosition().x, 2) + pow(playerPosition.y - node->getPosition().y, 2);
				nearestNode = node;
			}
		//}
	}
	return nearestNode;
}

//Implementation for A*
float Arena::calculateDistance(Node* currentNode, Node* targetedNode)
{
	float xDist, yDist;
	xDist = abs(currentNode->pos.x - targetedNode->pos.x);
	yDist = abs(currentNode->pos.y - targetedNode->pos.y);
	xDist *= xDist;
	yDist *= yDist;
	return xDist + yDist;
}

void Arena::startSearch(sf::Vector2f startingCoordinate, sf::Vector2f goalCoordinate)
{
	Node* startNode, * goalNode;
	startNode = getNearestNode(startingCoordinate);
	goalNode = getNearestNode(goalCoordinate);
	std::vector<Node*> openList;
	std::vector<Node*> closedList;
	this->startNode = startNode;
	this->goalNode = goalNode;
	Node* currentNode{ startNode };
	currentNode->gValue = 0;
	currentNode->setHValue(calculateDistance(startNode, goalNode));
	currentNode->setFValue();
	openList.emplace_back(startNode);
	while (currentNode != goalNode)
	{
		currentNode = openList.front();
		for (int i = 1; i < openList.size(); ++i)
		{
			if (openList[i]->getFValue() < currentNode->getFValue() ||
				openList[i]->getFValue() == currentNode->getFValue() && openList[i]->hValue == currentNode->hValue)
			{
				currentNode = openList[i];
			}
		}
		for (int i = 0; i < openList.size(); ++i)
		{
			if (openList[i] == currentNode)
			{
				openList.erase(openList.begin() + i);
				continue;
			}
		}
		closedList.emplace_back(currentNode);
		if (currentNode == goalNode)
		{
			currentPath = tracePath(currentNode);
			return;

		}
		for (auto& neighbourId : currentNode->neighbours)
		{
			Node* neighbourNode{ getNodeById(neighbourId) };
			if (!isInVectorList(neighbourNode, closedList))
			{
				int tentativeCostToNeighbour = currentNode->gValue + calculateDistance(currentNode, neighbourNode);
				if (tentativeCostToNeighbour < neighbourNode->gValue || !isInVectorList(neighbourNode, openList))
				{
					neighbourNode->setParentNode(currentNode);
					neighbourNode->setGValue(tentativeCostToNeighbour);
					neighbourNode->setHValue(calculateDistance(neighbourNode, goalNode));
					neighbourNode->setFValue();
					if (!isInVectorList(neighbourNode, openList))
					{
						openList.emplace_back(neighbourNode);
					}
				}
			}
		}
	}
}

bool Arena::isInVectorList(Node* node, std::vector<Node*> nodeList)
{
	return std::find(nodeList.begin(), nodeList.end(), node) != nodeList.end();
}

bool Arena::isLineSegmentIntersecting(sf::Vector2f a, sf::Vector2f b, sf::Vector2f c, sf::Vector2f d)
{
	float denominator = (a.x - b.x) * (c.y - d.y) - (a.y - b.y) * (c.x - d.x);
	if (denominator == 0) {
		return false;
	}
	float t = ((a.x - c.x) * (c.y - d.y) - (a.y - c.y) * (c.x - d.x)) / denominator;
	float u = -((a.x - b.x) * (a.y - c.y) - (a.y - b.y) * (a.x - c.x)) / denominator;
	//std::cout << t << " = ";
	return (t >= 0 && t <= 1) && (u >= 0 && u <= 1);
}

bool Arena::isLineSegmentIntersectingBlock(sf::Vector2f a, sf::Vector2f b, sf::RectangleShape block)
{
	int count = 0;
	sf::Vector2f topLeft = block.getPosition();
	sf::Vector2f topRight = sf::Vector2f(block.getPosition().x + block.getSize().x, block.getPosition().y);
	sf::Vector2f bottomRight = sf::Vector2f(block.getPosition().x + block.getSize().x, block.getPosition().y + block.getSize().y);
	sf::Vector2f bottomLeft = sf::Vector2f(block.getPosition().x, block.getPosition().y + block.getSize().y);

	if (isLineSegmentIntersecting(a, b, topLeft, topRight)) {
		count++;
		//cout << "Top " << endl;
	};
	if (isLineSegmentIntersecting(a, b, topRight, bottomRight)) {
		count++;
		//cout << "Right " << endl;
	};
	if (isLineSegmentIntersecting(a, b, bottomRight, bottomLeft)) {
		count++;
		//cout << "Bottom " << endl;
	};
	if (isLineSegmentIntersecting(a, b, bottomLeft, topLeft)) {
		count++;
		//cout << "Left " << endl;
	};
	return count == 0;
}

bool Arena::isInLineOfSight(sf::Vector2f a, sf::Vector2f b)
{
	for (int i = 0; i < noOfBlocks;i++) {
		if (!isLineSegmentIntersectingBlock(a, b, blocks[i])) return false;
	}
	return true;
}

std::vector<Node*> Arena::tracePath(Node* targetNode)
{
	std::vector<Node*> drawPath;
	while (targetNode != startNode)
	{
		drawPath.push_back(targetNode);
		targetNode = targetNode->parentNode;
	}
	std::reverse(drawPath.begin(), drawPath.end());
	return drawPath;
}