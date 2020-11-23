#include "Node.h"

int Node::counter = 0;

Node::Node()
{
}

Node::~Node()
{
	delete this;
}

Node::Node(sf::Vector2f position)
{
	id = counter;
	counter++;
	pos = position;
	parentNode = NULL;
	body.setPosition(position);
}


void Node::draw(sf::RenderWindow& window)
{
	window.draw(body);
}



void Node::add_to_neighbours(int id_number)
{
	/*neighbours[neighbours_count] = id_number;
	neighbours_count++;*/
	for (const auto neighbour : neighbours)
	{
		if (neighbour == id_number)
		{
			return;
		}
	}
	neighbours.push_back(id_number);
}

int Node::getId()
{
	return id;
}

sf::Vector2f Node::getPosition()
{
	return pos;
}

void Node::setGValue(const int gValue)
{
	this->gValue = gValue;
}

void Node::setHValue(const int hValue)
{
	this->hValue = hValue;
}

void Node::setFValue()
{
	fValue = gValue + hValue;
}

float Node::getFValue()
{
	return fValue;
}

void Node::setParentNode(Node* node)
{
	parentNode = node;
}