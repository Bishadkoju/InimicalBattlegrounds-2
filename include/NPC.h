#pragma once
#include "playerController.h"
#include "Player.h"
#include "Arena.h"
class NPC
{
private:
	Player *self, *e;
	sf::Clock mouseClickCooldownTimer;
	Arena* arena;
	playerController *controller;
	std::vector<sf::CircleShape> intersectionPointsCircles;
public:
	NPC();
	NPC(Player*, playerController*,Player*,Arena*);
	void update();
	void adjustPlayerDirection();
	bool isInLineOfSight(sf::Vector2f, sf::Vector2f);
	bool liesInBlock(sf::Vector2f point);
	void draw(sf::RenderWindow& window);
	void clickMouse(std::string);
};

