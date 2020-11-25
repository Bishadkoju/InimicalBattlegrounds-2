#pragma once
#include "playerController.h"
#include "Player.h"
#include "Arena.h"
#include "States/State.h"
class NPC
{
private:
	Player *self, *e;
	double detectionRadiusSquared = 100000;
	sf::Clock mouseClickCooldownTimer;
	Arena* arena;
	playerController *controller;
	std::vector<sf::CircleShape> intersectionPointsCircles;
	State* currentState;
public:
	NPC();
	NPC(Player*, playerController*,Player*,Arena*);
	void searchEnemy();
	void update();
	void adjustPlayerDirection();
	bool isInRange();
	bool isInLineOfSight(sf::Vector2f, sf::Vector2f);
	bool liesInBlock(sf::Vector2f point);
	void draw(sf::RenderWindow& window);
	void clickMouse(std::string);
	void changeState(State* nextState);
	void clearCurrentPath();
};

