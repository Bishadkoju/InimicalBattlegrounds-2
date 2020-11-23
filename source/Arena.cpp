#include "Arena.h"

Arena::Arena()
{
	textureBackImag.loadFromFile("pic/newarena.png");
	spriteBackGroundImage.setTexture(textureBackImag);
	spriteBackGroundImage.scale(2,1.3);
	//spriteBackGroundImage.getGlobalBounds();


	/*blocks[0].setFillColor(sf::Color(100, 250, 50));
	blocks[0].setSize(sf::Vector2f(100, 50));
	blocks[0].setPosition(900, 450);

	blocks[1].setFillColor(sf::Color(100, 250, 50));
	blocks[1].setSize(sf::Vector2f(100, 50));
	blocks[1].setPosition(400, 300);*/

	for (int i = 0; i < noOfBlocks; i++) {
		blocks[i].setFillColor(sf::Color::Transparent);
		blocks[i].setSize(sizes[i]);
		blocks[i].setPosition(positions[i]);
	}


}

void Arena::draw(sf::RenderWindow& window)
{
	window.draw(spriteBackGroundImage);
	/*if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		mp.x = sf::Mouse::getPosition().x;
		mp.y = sf::Mouse::getPosition().y;
		std::cout << "(" << mp.x << "," << mp.y << ")" << std::endl;
	}*/
	for (const auto block : blocks) {
		window.draw(block);
		
	}
	
	
}
