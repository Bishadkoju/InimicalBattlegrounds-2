#pragma once
#include<iostream>
#include<SFML/Audio.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/Network.hpp>
#include<SFML/Window.hpp>
#include<string>
#include"Player.h"
#include "Arena.h"
#include "playerController.h"
#include "GameClient.h"
#include "GameServer.h"
//#include "Server.h"
//#include "Client.h"
class Game
{
protected:
	bool isGameOver;
	bool isPlayerOne;
	Arena arena1;
	Player p,e;
	GameServer server;
	GameClient client;
	sf::RenderWindow window;
	int m_width, m_height;
	sf::Texture texture, brick,gOver,gWin,gLose;
	sf::Sprite sprite, sgOver,sgWin,sgLose;
	playerController userController,enemyController;
	//Client* client;
	//Server* server;
	////sf::VideoMode DesktopMode = sf::VideoMode::getDesktopMode();
	//int isHost;
	sf::CircleShape shape;
	
public:
	Game();
	Game(int width,int height,std::string ip,bool isPlayer1);
	void run();
	void handleKeyboardInput(sf::Keyboard::Key key, bool isPressed);
	void processEvents();
	void update(sf::Time);
	void render();
	void collision();
};

