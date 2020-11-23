#include "SoloGame.h"
SoloGame::SoloGame(int width, int height )
	:window(sf::VideoMode(width, height), "Inimical BattleGrounds", sf::Style::Fullscreen)
{
	//window.setFramerateLimit(120);
	m_height = height;
	m_width = width;
	texture.loadFromFile("pic/army1.png");
	if (!texture.loadFromFile("pic/army1.png"))
	{

	}
	gOver.loadFromFile("pic/gameover.png");
	gWin.loadFromFile("pic/win.png");
	gLose.loadFromFile("pic/lose.png");
	isGameOver = false;

	sgOver.setTexture(gOver);
	sgLose.setTexture(gLose);
	sgWin.setTexture(gWin);

	sgOver.setPosition(300, 300);
	sgWin.setPosition(600, 600);
	sgLose.setPosition(400, 600);
	p.setArena(arena1);
	e.setArena(arena1);
	//e.setCoordinate(sf::Vector2f(0, 800));
	npc = new NPC(&e, &enemyController,&p,&arena1);

}


void SoloGame::run()
{
	sf::Clock clock;

	p.initialize("4", sf::Vector2f(300, 500));
	e.initialize("3", sf::Vector2f(400, 800));
	while (window.isOpen())
	{
		sf::Time deltaTime = clock.restart();
		processEvents();
		update(deltaTime);
		render();
	}
}

void SoloGame::handleKeyboardInput(sf::Keyboard::Key key, bool isPressed)
{

	if (key == sf::Keyboard::A) {
		//p.isPressedLeft = isPressed;
		userController.isPressedLeft = isPressed;

	}
	else if (key == sf::Keyboard::D) {
		//p.isPressedRight = isPressed;
		userController.isPressedRight = isPressed;
	}

	if (key == sf::Keyboard::W) {
		//p.isPressedUp = isPressed;
		userController.isPressedUp = isPressed;
	}


}

void SoloGame::processEvents()
{

	userController.mousePosition = sf::Vector2f(sf::Mouse::getPosition(window));
	userController.isLeftMouseButtonPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
	userController.isRightMouseButtonPressed = sf::Mouse::isButtonPressed(sf::Mouse::Right);

	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			handleKeyboardInput(event.key.code, true);
			break;
		case sf::Event::KeyReleased:
			handleKeyboardInput(event.key.code, false);
			break;
		case sf::Event::Closed:
			window.close();
			break;
		default:
			break;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			window.close();


	}
}

void SoloGame::update(sf::Time deltaTime)
{
	//isGameOver = p.isAlive || e.isAlive;
	if (!isGameOver) {
		p.update(deltaTime, userController, e);
		npc->update();
		e.update(deltaTime, enemyController, p);
		isGameOver = !(p.isAlive && e.isAlive);
	}


}

void SoloGame::render()
{
	window.clear();
	arena1.draw(window);
	p.draw(window);
	e.draw(window);
	npc->draw(window);

	sf::Sprite sprite(texture);
	sprite.setPosition(p.getCoordinate().x, p.getCoordinate().y);
	//window.draw(sprite);
	if (isGameOver)
	{
		window.draw(sgOver);
		if (p.isAlive) {
			window.draw(sgWin);
		}
		else {
			window.draw(sgLose);
		}
	}
	window.display();

}

void SoloGame::collision()
{

	if (p.getCoordinate().y >= 700) {
		p.isCollided = true;

		p.setCoordinate(p.getCoordinate().x, 700);
	}
	else {
		p.isCollided = false;
	}

}

