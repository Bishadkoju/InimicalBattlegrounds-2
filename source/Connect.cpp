
#include "Connect.h"

Connect::Connect(int width, int height) :window(sf::VideoMode(width, height), "Connect",sf::Style::Fullscreen)
{ //logo
	for (int i = 0; i < 3; i++){
		selectedItem[i] = false;

	}
	font.loadFromFile("pic/Font/DejaVuSans.ttf");
	ipLocal.setString("Your IP Address is " + sf::IpAddress::getLocalAddress().toString());
	std::cout << sf::IpAddress::getLocalAddress().toString() << std::endl;
	ipLocal.setFillColor(sf::Color::Green);
	//ipLocal.setCharacterSize(20);
	ipLocal.setPosition(0, 10);
	ipLocal.setFont(font);

	
	inputBox.setSize(sf::Vector2f(230, 50));
	inputBox.setPosition(250, 100);
	inputBox.setOutlineColor(sf::Color::Blue);
	inputBox.setOutlineThickness(5);
	inputBox.setFillColor(sf::Color::Transparent);
	playerInput.setPosition(260, 110);
	playerInput.setFont(font);


	menuItems[0].setString("Player 1");
	menuItems[1].setString("Player 2");
	menuItems[2].setString("Exit");

	for (int i = 0; i < 3; i++) {
		menuItems[i].setFont(font);
		menuItems[i].setPosition(200, 200 + i * 100);
		menuBox[i].setPosition(180, 180 + i * 100);
		menuBox[i].setFillColor(sf::Color::Green);
		menuBox[i].setSize(sf::Vector2f(400, 80));
		menuBox[i].setOutlineColor(sf::Color::Blue);
	}


}

void Connect::run()
{
	
	while (window.isOpen())
	{
		processInput();
		update();
		render();
	}
}

void Connect::processInput()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		mousePosition = sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::TextEntered:
			if ((event.text.unicode >= 48 && event.text.unicode <= 57) || (event.text.unicode == 46))
			{
				inputText += event.text.unicode;
				playerInput.setString(inputText);
			}
			else if (event.text.unicode == 8 && !inputText.isEmpty())
			{
				inputText.erase(inputText.getSize() - 1, 1);
				playerInput.setString(inputText);
			}
			break;
		
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			if (selectedItem[0] && inputText.getSize()!=0) {
				std::cout << "server";
				window.close();
				Game g(800, 800, inputText, true);
				g.run();
			}
			else if (selectedItem[1] && inputText.getSize() != 0) {
				std::cout << "client";
				window.close();
				Game g(800, 800, inputText, false);
				g.run();

			}else if(selectedItem[2]){
				window.close();
				std::cout << "exit";
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			window.close();
	}
}

void Connect::update()
{
	//std::cout << selectedItem[0] << selectedItem[1] << selectedItem[2] << std::endl;
	for (int i = 0; i < 3; i++) {
		if (menuBox[i].getGlobalBounds().contains(mousePosition)) {
			menuBox[i].setOutlineThickness(10);
			selectedItem[i] = true;
			//std::cout << "hello";
		}
		else {
			menuBox[i].setOutlineThickness(0);
			selectedItem[i] = false;
		}
	}
		
	
}

void Connect::render()
{
	window.clear();
	window.draw(ipLocal);
	window.draw(inputBox);
	window.draw(playerInput);
	for (int i = 0; i < 3; i++) {
		window.draw(menuBox[i]);
		window.draw(menuItems[i]);
	}
	window.display();
}

