#pragma once
#include "playerController.h"
#include "Player.h"
#include "Arena.h"
#include "States/State.h"
class NPC
{
private:
	Player *self, *e;
	float PI = 3.141592654;
	Arena* arena;
	playerController *controller;
	State* currentState;

	std::vector<sf::CircleShape> intersectionPointsCircles;
	sf::Clock mouseClickCooldownTimer;
	float buttonPressInterval = 800;
	sf::Clock wanderTimer;
	float wanderCircleRadius =50;
	float wanderCircleOffset =300;
	
	
public:
	NPC();

	NPC(Player*, playerController*,Player*,Arena*);
	sf::Vector2f target;
	double detectionRadiusSquared = 100000;
	
	void adjustPlayerDirection();
	bool canFight();
	void changeState(State* nextState);
	void clearCurrentPath();
	void clickMouse(std::string);
	void draw(sf::RenderWindow& window);
	void fire();
	void flee();
	void followPath();
	sf::Vector2f getFleeDirection();
	bool isEnemyInSight();
	bool isInRange(float distance);
	bool liesInBlock(sf::Vector2f point);
	void playerMoveTo(sf::Vector2f goalCoordinate);
	void resetKeyboardPress();
	void searchEnemy();
	
	void update();
	void wander();
};

