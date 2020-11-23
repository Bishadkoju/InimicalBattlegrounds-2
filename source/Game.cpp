#include "Game.h"
Game::Game(int width, int height,std::string Ip,bool isPlayer1)
	:window(sf::VideoMode(width, height),"Inimical BattleGrounds",sf::Style::Fullscreen),
	isPlayerOne(isPlayer1),
	server(isPlayer1 ? 11000 : 10000),
	client(Ip, isPlayer1 ? 10000 : 11000)

{
	std::cout<<Ip<<"Player 1"<<isPlayer1<<std::endl;
	//window.setFramerateLimit(120);
	m_height = height;
	m_width=width;
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

}
	

void Game::run()
{
	sf::Clock clock;
	
	p.initialize("4",sf::Vector2f(300,500));
	e.initialize("3",sf::Vector2f(400,800));
	while (window.isOpen())
	{
		sf::Time deltaTime = clock.restart();
		processEvents();
		update(deltaTime);
		render();
	}
}

void Game::handleKeyboardInput(sf::Keyboard::Key key, bool isPressed)
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

void Game::processEvents()
{

	//p.mousePosition = sf::Vector2f(sf::Mouse::getPosition(window));
	//p.isLeftMouseButtonPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
	userController.mousePosition = sf::Vector2f(sf::Mouse::getPosition(window));
	userController.isLeftMouseButtonPressed= sf::Mouse::isButtonPressed(sf::Mouse::Left);
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

void Game::update(sf::Time deltaTime)
{
	//isGameOver = p.isAlive || e.isAlive;
	if (!isGameOver) {

			/*p.update(deltaTime, isPlayerOne?userController:enemyController, e);
			server.update(isPlayerOne ? userController : enemyController);
			enemyController = client.getRecievedData();
			e.update(deltaTime, isPlayerOne ? enemyController : userController, p);*/
		if (isPlayerOne) {
			p.update(deltaTime, userController, e);
			server.update(userController);
			enemyController = client.getRecievedData();
			e.update(deltaTime, enemyController, p);
		}
		else {
			p.update(deltaTime, enemyController, e);
			server.update(userController);
			enemyController = client.getRecievedData();
			e.update(deltaTime, userController, p);
		}
		
		
		isGameOver = !(p.isAlive && e.isAlive);
	}
	
	
}

void Game::render()
{
	window.clear();
	arena1.draw(window);
	p.draw(window);
	e.draw(window);
	
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

void Game::collision()
{
	
	if (p.getCoordinate().y >= 700 ) {
		p.isCollided = true;
		
		p.setCoordinate(p.getCoordinate().x, 700);
	}
	else {
		p.isCollided = false;
	}

}

