
#include "MainMenu.h"

MainMenu::MainMenu(int width, int height) :window(sf::VideoMode(width,height), "Main",sf::Style::Fullscreen)
{ //logo
	audioManager = new Audio(100);
	audioManager->load(Theme, "AudioAssets/theme.wav");
	audioManager->playSound(Theme);
	texture.loadFromFile("pic/font/logo.png");
	
	sprite.setTexture(texture);
	sprite.setPosition(sf::Vector2f(480, -25));
	sprite.scale(2, 2);
	//actual photo of play and exit button
	//single play button
	splayTexture.loadFromFile("pic/font/splay.png");
	
	splaySprite.setTexture(splayTexture);
	splaySprite.setPosition(sf::Vector2f(760, 550));

	//multiplay button
	mplayTexture.loadFromFile("pic/font/mplay.png");

	mplaySprite.setTexture(mplayTexture);
	mplaySprite.setPosition(sf::Vector2f(760, 650));

	//exit button
	exitTexture.loadFromFile("pic/font/exit.png");
	
	exitSprite.setTexture(exitTexture);
	exitSprite.setPosition(sf::Vector2f(760, 750));
	//for on mouse hover
	//on mouse hover on single play button
	splayTexture1.loadFromFile("pic/font/splay1.png");

	splaySprite1.setTexture(splayTexture1);
	splaySprite1.setPosition(sf::Vector2f(760, 550));

	//on mouse hover on multi play button
	mplayTexture1.loadFromFile("pic/font/mplay1.png");

	mplaySprite1.setTexture(mplayTexture1);
	mplaySprite1.setPosition(sf::Vector2f(760, 650));
	//on mouse hover on exit button
	exitTexture1.loadFromFile("pic/font/exit1.png");
	
	exitSprite1.setTexture(exitTexture1);
	exitSprite1.setPosition(sf::Vector2f(760, 750));

}

void MainMenu::display()
{
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window.close();
		}
		window.clear();
		window.draw(sprite);
		window.draw(splaySprite1);
		window.draw(mplaySprite1);
		window.draw(exitSprite1);
		if (isSpriteHover(mplaySprite1.getGlobalBounds()))
		{
			window.draw(mplaySprite);
			window.draw(splaySprite1);
			window.draw(exitSprite1);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				//std::cout << "clicked" 
				
				window.close();
				delete audioManager;
				Connect c(800, 800);
				c.run();
				
				/*Game game(1377, 720);
				game.run();*/
				
				std::cout << "exitted" << std::endl;
			}
		}
		if (isSpriteHover(exitSprite1.getGlobalBounds()))
		{
			window.draw(exitSprite);
			window.draw(mplaySprite1);
			window.draw(splaySprite1);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				//std::cout << "exitclicked"<<std::endl;
				exit(0);
				
			}
		}
		if (isSpriteHover(splaySprite.getGlobalBounds()))
		{
			window.draw(exitSprite1);
			window.draw(mplaySprite1);
			window.draw(splaySprite);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				std::cout << "Clicked"<<std::endl;
				window.close();
				delete audioManager;
				SoloGame solo(800, 800);
				solo.run();

			}
		}
		window.display();
	}
}

bool MainMenu::isSpriteHover(sf::FloatRect sp)
{
	mousePosition.x = sf::Mouse::getPosition(window).x;
	mousePosition.y = sf::Mouse::getPosition(window).y;
	if (sp.contains(mousePosition))
	{
		return true;
	}
	else
	{
		return false;
	}
}
