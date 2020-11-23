#include "Bullet.h"

Bullet::Bullet(sf::Vector2f startingCoordinate, sf::Vector2f direction, float velocity, float damagePoints)
{
	coordinate=(startingCoordinate);
	this->direction = direction;
	this->damagePoints = damagePoints;
	this->velocity = velocity;
	body.setSize(sf::Vector2f(5.f, 5.f));
	body.setFillColor(sf::Color(255, 0, 0, 255));
}

Bullet::~Bullet()
{
	//std::cout << "Bullet Destroyed" << std::endl;
}


void Bullet::update(sf::Time deltaTime)
{
	this->deltaTime = deltaTime;
	coordinate.x += direction.x*velocity * deltaTime.asSeconds();
	coordinate.y += direction.y*velocity * deltaTime.asSeconds();
	body.setPosition(coordinate);
	
}

void Bullet::draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void Bullet::destroy()
{
	delete this;
}
