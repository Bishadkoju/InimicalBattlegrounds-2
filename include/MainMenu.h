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
	sf::Texture texture, splayTexture, exitTexture, splayTexture1, exitTexture1,mplayTexture,mplayTexture1;
	sf::Sprite sprite, splaySprite, exitSprite, splaySprite1, exitSprite1,mplaySprite,mplaySprite1;
	sf::Vector2f mousePosition;
public:
	MainMenu( int width,int height);
	void display();
	bool isSpriteHover(sf::FloatRect sp);
};

