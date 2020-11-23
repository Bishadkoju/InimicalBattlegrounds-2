#include "Collider.h"

Collider::Collider(sf::RectangleShape& body):body(body){}



bool Collider::checkCollision(sf::RectangleShape & other)
{
	//this->other = other;
	return body.getGlobalBounds().intersects(other.getGlobalBounds(),intersection);
	
}

sf::FloatRect Collider::getGlobalBounds()
{
	return this->body.getGlobalBounds();
}

sf::FloatRect Collider::getIntersection()
{
	return intersection;
}



