#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>

#include "Node.h"
#include<iostream>
class Arena
{
public:
	bool showNode = false;
	bool showEdge = false;
	bool showPath = false;
	static constexpr int noOfBlocks = 34;
	sf::RectangleShape blocks[noOfBlocks];
	std::vector<Node*> node_object;
	sf::RectangleShape limit_box;
	int step = 40;
	std::vector<sf::Vector2f>direction;
	Node* startingNode;
	//sf::Vector2f sizes[noOfBlocks], positions[noOfBlocks];
	//sf::Vector2f mp;
	sf::Vector2f sizes[noOfBlocks] = {
		sf::Vector2f(103,360),sf::Vector2f(83,50),sf::Vector2f(51,202),sf::Vector2f(225,37),sf::Vector2f(97,72),
		sf::Vector2f(285,60),sf::Vector2f(33,12),sf::Vector2f(83,13),sf::Vector2f(712,57),sf::Vector2f(71,10),
		sf::Vector2f(100,63),sf::Vector2f(116,55),sf::Vector2f(320,55),sf::Vector2f(123,57),sf::Vector2f(79,70),
		sf::Vector2f(78,68),sf::Vector2f(102,65),sf::Vector2f(396,45),sf::Vector2f(80,127),sf::Vector2f(326,50),
		sf::Vector2f(140,36),sf::Vector2f(80,164),sf::Vector2f(687,37),sf::Vector2f(319,22),sf::Vector2f(227,14),
		sf::Vector2f(194,15),sf::Vector2f(82,21),sf::Vector2f(378,57),sf::Vector2f(85,117),sf::Vector2f(294,57),
		sf::Vector2f(123,59),sf::Vector2f(164,52),sf::Vector2f(92,31),sf::Vector2f(178,61)
	};
	sf::Vector2f positions[noOfBlocks] = {
		sf::Vector2f(181,390),sf::Vector2f(181,376),sf::Vector2f(181,174),sf::Vector2f(284,713),sf::Vector2f(419,531),
		sf::Vector2f(233,175),sf::Vector2f(232,234),sf::Vector2f(435,234),sf::Vector2f(518,190),sf::Vector2f(438,378),
		sf::Vector2f(417,387),sf::Vector2f(509,381),sf::Vector2f(708,382),sf::Vector2f(1105,383),sf::Vector2f(627,246),
		sf::Vector2f(1027,246),sf::Vector2f(815,315),sf::Vector2f(723,528),sf::Vector2f(1036,572),sf::Vector2f(1116,649),
		sf::Vector2f(1364,451),sf::Vector2f(1362,486),sf::Vector2f(740,891),sf::Vector2f(1149,868),sf::Vector2f(1119,928),
		sf::Vector2f(1123,942),sf::Vector2f(1183,956),sf::Vector2f(1471,723),sf::Vector2f(1762,778),sf::Vector2f(1469,837),
		sf::Vector2f(365,890),sf::Vector2f(707,727),sf::Vector2f(1191,557),sf::Vector2f(1613,347)
	};
	Arena();
	void draw(sf::RenderWindow& window);
	sf::Texture textureBackImag;
	sf::Sprite spriteBackGroundImage;
	bool is_freespace(sf::Vector2f position);
	bool nodeExists(sf::Vector2f position);
	Node* getnode(sf::Vector2f position);
	void expandNode(Node* self);
	Node* createNode(sf::Vector2f position);
	Node* getNodeById(int id);
	Node* getNearestNode(sf::Vector2f playerPosition);
	//for pathfinding
	Node* startNode;
	Node* goalNode;
	std::vector<Node*> currentPath;
	float calculateDistance(Node* currentNode, Node* targetedNode);
	void startSearch(sf::Vector2f startingCoordinate, sf::Vector2f goalCoordinate);
	bool isInVectorList(Node* node, std::vector<Node*> nodeList);
	bool isInLineOfSight(sf::Vector2f a, sf::Vector2f b);
	std::vector<Node*> tracePath(Node* targetNode);
private:
	bool isLineSegmentIntersecting(sf::Vector2f a, sf::Vector2f b, sf::Vector2f c, sf::Vector2f d);
	bool isLineSegmentIntersectingBlock(sf::Vector2f a, sf::Vector2f b, sf::RectangleShape block);
};