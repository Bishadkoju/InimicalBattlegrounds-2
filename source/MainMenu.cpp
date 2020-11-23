
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
	//play button
	playTexture.loadFromFile("pic/font/play.png");
	
	playSprite.setTexture(playTexture);
	playSprite.setPosition(sf::Vector2f(840, 500));

	playSoloButton.setSize(sf::Vector2f(100, 50));
	playSoloButton.setFillColor(sf::Color::Blue);
	playSoloButton.setPosition(sf::Vector2f(840, 800));
	//exit button
	exitTexture.loadFromFile("pic/font/exit.png");
	
	exitSprite.setTexture(exitTexture);
	exitSprite.setPosition(sf::Vector2f(840, 600));
	//for on mouse hover
	//on mouse hover on play button
	playTexture1.loadFromFile("pic/font/play1.png");

	playSprite1.setTexture(playTexture1);
	playSprite1.setPosition(sf::Vector2f(840, 500));
	//on mouse hover on exit button
	exitTexture1.loadFromFile("pic/font/exit1.png");
	
	exitSprite1.setTexture(exitTexture1);
	exitSprite1.setPosition(sf::Vector2f(840, 600));

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
		window.draw(playSprite1);
		window.draw(exitSprite1);
		window.draw(playSoloButton);
		if (isSpriteHover(playSprite1.getGlobalBounds()))
		{
			window.draw(playSprite);
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
			window.draw(playSprite1);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				//std::cout << "exitclicked"<<std::endl;
				exit(0);
				
			}
		}
		if (isSpriteHover(playSoloButton.getGlobalBounds()))
		{
			std::cout << "HOvered" << "\n";
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
