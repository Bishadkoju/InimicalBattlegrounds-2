#include "playerController.h"

playerController::playerController(bool isPressedLeft, bool isPressedRight, bool isPressedUp, bool isLeftMouseButtonPressed, bool isRightMouseButtonPressed, sf::Vector2f mousePosition)
{
	this->isPressedLeft = isPressedLeft;
	this->isPressedRight = isPressedRight;
	this->isPressedUp=isPressedUp;
	this->isLeftMouseButtonPressed = isLeftMouseButtonPressed;
	this->isRightMouseButtonPressed=isRightMouseButtonPressed;
	this->mousePosition= mousePosition;
}

playerController::playerController()
{
	this->isPressedLeft = false;
	this->isPressedRight = false;
	this->isPressedUp = false;
	this->isLeftMouseButtonPressed = false;
	this->isRightMouseButtonPressed = false;
	this->mousePosition = sf::Vector2f(0, 0);
}
