#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
class Bullet
{
private:
	sf::Vector2f direction;
	float velocity;
	
	sf::Time deltaTime;
	sf::Vector2f coordinate;

	
public:
	Bullet(sf::Vector2f startingCoordinate,sf::Vector2f direction,float velocity,float damagePoints);
	~Bullet();
	sf::RectangleShape body;
	float damagePoints;
	//void setDirection(sf::Vector2f direction);
	void update(sf::Time deltaTime);
	void draw(sf::RenderWindow& window);
	void destroy();

};

