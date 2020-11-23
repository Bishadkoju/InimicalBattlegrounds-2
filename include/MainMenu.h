#pragma 
#include<SFML/Graphics.hpp>
#include<iostream>
#include "SoloGame.h"
#include "Connect.h"

class MainMenu
{
private:
	Audio *audioManager;
	sf::RenderWindow window;
	sf::Texture texture, playTexture, exitTexture, playTexture1, exitTexture1;
	sf::Sprite sprite, playSprite, exitSprite, playSprite1, exitSprite1;
	sf::RectangleShape playSoloButton;
	sf::Vector2f mousePosition;
public:
	MainMenu( int width,int height);
	void display();
	bool isSpriteHover(sf::FloatRect sp);
};

