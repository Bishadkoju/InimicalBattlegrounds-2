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
#include "NPC.h"
//#include "Server.h"
//#include "Client.h"
class SoloGame
{
protected:
	bool isGameOver;
	Arena arena1;
	Player p, e;
	NPC *npc;
	
	sf::RenderWindow window;
	int m_width, m_height;
	sf::Texture texture, brick, gOver, gWin, gLose;
	sf::Sprite sprite, sgOver, sgWin, sgLose;
	playerController userController, enemyController;
	//Client* client;
	//Server* server;
	////sf::VideoMode DesktopMode = sf::VideoMode::getDesktopMode();
	//int isHost;
	sf::CircleShape shape;

public:
	SoloGame(int width, int height);
	void run();
	void handleKeyboardInput(sf::Keyboard::Key key, bool isPressed);
	void processEvents();
	void update(sf::Time);
	void render();
	void collision();
};

