#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<iostream>
class Node
{
private:
	static int counter;
	int id;
public:
	sf::Vector2f pos;
	float gValue;
	float hValue;
	float fValue;
	Node* parentNode;
	std::vector<int> neighbours;
	Node();
	~Node();
	Node(sf::Vector2f position);
	static constexpr int noOfNodes = 68;
	sf::CircleShape body;
	void draw(sf::RenderWindow& window);
	void add_to_neighbours(int id_number);
	int getId();
	sf::Vector2f getPosition();
	void setGValue(const int gValue);
	void setHValue(const int hValue);
	void setFValue();
	float getFValue();
	void setParentNode(Node* node);
};