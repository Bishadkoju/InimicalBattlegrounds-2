
#include<iostream>
#include "MainMenu.h"
#include "Connect.h"
#include "SoloGame.h"

int main()
{
	/*MainMenu menu(800, 800);
menu.display();*/
SoloGame solo(800, 800);
solo.run();

//Game game(800, 800);
//	game.run();

	/*Connect connect(800, 800);
	connect.run();*/


	return 0;
}

