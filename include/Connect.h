#pragma once
#include<iostream>
#include "Game.h"
#include<SFML/Graphics.hpp>

class Connect
{
private:
	//Audio* audioManager;
	sf::RenderWindow window;
	sf::Text ipLocal,playerInput, menuItems[3];
	sf::Vector2f mousePosition;
	sf::RectangleShape menuBox[3],inputBox;
	sf::String inputText;
	sf::Font font;
	bool selectedItem[3];
public:
	Connect(int width, int height);
	void run();
	void processInput();
	void update();
	void render();
};

