#include "NPC.h"
#include "States/WanderState.h"

NPC::NPC(Player* self, playerController* controller, Player* enemy,Arena* arena) {
	this->self = self;
	this->controller = controller; 
	this->e = enemy;
	this->arena = arena;
	currentState = WanderState::Instance();
	currentState->enter(this);
	target = sf::Vector2f(500, 800);
}

void NPC::searchEnemy()
{
	this->arena->startSearch(self->getCoordinate(), e->getCoordinate());
}

void NPC::update()
{
	if (currentState) {
		currentState->execute(this);
	}
	
}

void NPC::adjustPlayerDirection()
{
	controller->mousePosition = e->getCenter();
}

bool NPC::canFight()
{
	return self->health>50;
}

bool NPC::isInRange(float distance)
{
	float distanceSquared = pow(self->getCoordinate().x - e->getCoordinate().x, 2) + pow(self->getCoordinate().y - e->getCoordinate().y, 2);
	return (distanceSquared < distance);
}

bool NPC::isEnemyInSight()
{
	return arena->isInLineOfSight(self->getCenter(),e->getCenter()) ;
}

bool NPC::liesInBlock(sf::Vector2f point) {
	for (const auto block : arena->blocks) {
		if (block.getGlobalBounds().contains(point) ){
			return true;
		}
	}
	return false;
}

void NPC::draw(sf::RenderWindow& window)
{

	//sf::Vector2f a = sf::Vector2f(sf::Mouse::getPosition(window));
	////std::cout <<self->getCoordinate().x<<"-"<<self->getCoordinate().y <<"=" <<arena->isInLineOfSight(self->getCoordinate(), e->getCoordinate()) << std::endl;
	//std::cout << isEnemyInSight() << std::endl;
	for (int i = 0; i < intersectionPointsCircles.size(); i++) {
		window.draw(intersectionPointsCircles[i]);
	}
}

void NPC::fire()
{
	if (self->bulletsOnRound > 0) {
		clickMouse("left");
	}
	else {
		clickMouse("right");
	}
}

void NPC::flee()
{
	if (wanderTimer.getElapsedTime().asMilliseconds() > 1000) {
		sf::Vector2f circlePosition = self->getCenter() - wanderCircleOffset * getFleeDirection();
		float randomAngle = (std::rand() % 360) * PI / 180;
		target = wanderCircleRadius * sf::Vector2f(cos(randomAngle), sin(randomAngle)) + circlePosition;
		controller->mousePosition = target;

		wanderTimer.restart();
	}
	//playerMoveTo(target);
	this->arena->startSearch(self->getCoordinate(), target);
	followPath();
}

void NPC::changeState(State* nextState)
{
	if (currentState && nextState) {
		currentState->exit(this);
		currentState = nextState;
		nextState->enter(this);
	}
}

void NPC::clearCurrentPath()
{
	arena->currentPath.clear();
}

void NPC::clickMouse(std::string button)
{
	if (button == "left") {
		controller->isLeftMouseButtonPressed = false;
		if (mouseClickCooldownTimer.getElapsedTime().asMilliseconds() > buttonPressInterval) {
			controller->isLeftMouseButtonPressed = true;
			mouseClickCooldownTimer.restart();
		}
	}
	else if (button == "right") {
		controller->isRightMouseButtonPressed = false;
		if (mouseClickCooldownTimer.getElapsedTime().asMilliseconds() > buttonPressInterval) {
			controller->isRightMouseButtonPressed = true;
			mouseClickCooldownTimer.restart();
		}
	}
}

void NPC::playerMoveTo(sf::Vector2f goalCoordinate)
{
	controller->isPressedLeft = (goalCoordinate.x < self->getCoordinate().x);
	controller->isPressedRight = (goalCoordinate.x > self->getCoordinate().x);
	controller->isPressedUp = (goalCoordinate.y < self->getCoordinate().y);
	//controller->mousePosition = goalCoordinate;
	

}

void NPC::followPath()
{
	if (arena->currentPath.size() > 0) {
		playerMoveTo(arena->currentPath[0]->getPosition());
	}
}

sf::Vector2f NPC::getFleeDirection()
{
	sf::Vector2f differenceVector = this->e->getCoordinate() - this->self->getCoordinate();
	float magnitude = std::sqrt(std::pow(differenceVector.x, 2) + std::pow(differenceVector.y, 2));
	return (1/magnitude)*differenceVector;
}

void NPC::wander()

{
	if (wanderTimer.getElapsedTime().asMilliseconds() > 1000) {
		sf::Vector2f circlePosition = self->getCenter() + wanderCircleOffset * self->getNormalVelocity();
		float randomAngle = (std::rand() % 360) * PI / 180;
		target = wanderCircleRadius * sf::Vector2f(cos(randomAngle), sin(randomAngle)) + circlePosition;
		controller->mousePosition = target;

		wanderTimer.restart();
	}
	//playerMoveTo(target);
		this->arena->startSearch(self->getCoordinate(), target);
		followPath();
	
}

void NPC::resetKeyboardPress()
{
	//controller->isLeftMouseButtonPressed = false;
	//controller->isRightMouseButtonPressed = false;
	controller->isPressedLeft = false;
	controller->isPressedRight = false;
	controller->isPressedUp = false;
}

