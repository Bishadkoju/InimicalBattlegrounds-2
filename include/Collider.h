#pragma once
#include <SFML/Graphics.hpp>
#include<iostream>
class Collider
{
public:
	Collider(sf::RectangleShape& body);
	bool checkCollision(sf::RectangleShape& other);
	sf::FloatRect getGlobalBounds();
	sf::FloatRect intersection;
	sf::FloatRect getIntersection();
	bool isIntersected;
	

private:
	sf::RectangleShape& body;
	//sf::RectangleShape& other;
};

