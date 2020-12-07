#include "NPC.h"
#include "States/WanderState.h"

NPC::NPC(Player* self, playerController* controller, Player* enemy,Arena* arena) {
	this->self = self;
	this->controller = controller; 
	this->e = enemy;
	this->arena = arena;
	currentState = WanderState::Instance();
	currentState->enter(this);
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
	controller->mousePosition = e->getCoordinate();
}

bool NPC::isInRange(float distance)
{
	float distanceSquared = pow(self->getCoordinate().x - e->getCoordinate().x, 2) + pow(self->getCoordinate().y - e->getCoordinate().y, 2);
	return (distanceSquared < distance);
}

bool NPC::isInLineOfSight(sf::Vector2f start, sf::Vector2f end)
{
	
	//float stepSize = 2,slope,tempX,tempY;
	//std::vector<sf::Vector2f> intermediatePoints;
	//sf::Vector2f difference;
	//slope = (end.y - start.y) / (end.x / start.x);
	//difference = end - start;
	////std::cout << difference.x<<','<<difference.y;
	////Generate Intermediate Points
	//for (int i = 1; i <= abs(difference.x) / stepSize; i++) {
	//	if(start.x<end.x){
	//		tempX = start.x + i * stepSize;
	//	}
	//	else {
	//		tempX = start.x - i * stepSize;
	//	}
	//	tempY = slope * (tempX - start.x) + start.y;
	//	intermediatePoints.push_back(sf::Vector2f(tempX, tempY));
	//	intersectionPointsCircles.push_back(sf::CircleShape(3));
	//}
	////std::cout << intermediatePoints.size();
	//
	//for (int i = 0; i < intermediatePoints.size();i++) {
	//	intersectionPointsCircles[i].setOrigin(intermediatePoints[i]);
	//	intersectionPointsCircles[i].setFillColor(sf::Color::Red);
	//	if (liesInBlock(intermediatePoints[i])) {
	//		return false;
	//	}
	//	
	//}
	//std::cout << std::endl;
	return false;

	
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
	for (int i = 0; i < intersectionPointsCircles.size(); i++) {
		window.draw(intersectionPointsCircles[i]);
	}
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

void NPC::playerMoveTo(sf::Vector2f goalCoordinate)
{
	controller->isPressedLeft = (goalCoordinate.x < self->getCoordinate().x);
	controller->isPressedRight = (goalCoordinate.x > self->getCoordinate().x);
	controller->isPressedUp = (goalCoordinate.y < self->getCoordinate().y);
	

}

void NPC::chaseEnemy()
{
	playerMoveTo(arena->currentPath[0]->getPosition());
}

void NPC::resetButtonPress()
{
	controller->isLeftMouseButtonPressed = false;
	controller->isRightMouseButtonPressed = false;
	controller->isPressedLeft = false;
	controller->isPressedRight = false;
	controller->isPressedUp = false;
}

