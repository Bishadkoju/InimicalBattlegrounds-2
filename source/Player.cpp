#include "Player.h"

Player::Player():isPressedLeft(false),isPressedRight(false),isPressedUp(false),isCollided(false),isOnGround(false),audioManager(100),isAlive(true)
{
	audioManager.load(PlayerFiring, "AudioAssets/gun.wav");
	audioManager.load(PlayerReloading, "AudioAssets/gunReload.wav");
	healthTexture.loadFromFile("pic/avatar/health.png");
	fuelTexture.loadFromFile("pic/avatar/fuel.png");

	healthBox.setSize(sf::Vector2f(health / 2.f, 5.f));
	//healthBox.setFillColor(sf::Color::Red);
	healthOutlineBox.setSize(sf::Vector2f(health / 2.f, 7.5f));

	fuelBox.setSize(sf::Vector2f(fuel / 20.f, 7.5f));
	fuelOutlineBox.setSize(sf::Vector2f(fuel / 20.f, 7.5f));
	bulletTexture.loadFromFile("pic/avatar/bullet.png");
	ammoTexture.loadFromFile("pic/avatar/reload.png");

	healthSprite.setTexture(healthTexture);
	healthSprite.setScale(0.01, 0.01);

	fuelSprite.setTexture(fuelTexture);
	fuelSprite.setScale(0.05, 0.05);

	for (int i = 0; i < 6; i++) {
		bulletSprite[i].setTexture(bulletTexture);
		bulletSprite[i].setScale(0.02, 0.02);
	}
	ammoSprite.setTexture(ammoTexture);
	ammoSprite.setScale(0.1, 0.1);

	totalBullets = 36;
	bulletsPerRoundMaximum = 6;
	bulletsOnRound = 6;
	
	isReloading = false;


	coordinate.x = 200;
	coordinate.y = 200;
	currentVelocity.x = 0;
	currentVelocity.y = 0;
	targetVelocity.x = 0;
	targetVelocity.y = 0;
	maxGroundVelocity.x =20;
	maxAirVelocity.x = 40;
	maxAirVelocity.y = 70;
	thrustValue = 80;

	texture.loadFromFile("pic/army1.png");
	scale = 0.35;
	body.setSize(sf::Vector2f(28.f, 50.f));
	//body.setRotation(60.f);

	groundDampingConstant = 500;
	airDampingConstant = 50;
	gravity = 50;
	elasticConstant = 0.3f;
	collider = (new Collider(body));
	//collider.body = this->body;

	noKeyWasPressed = true;
	//directions
	facingRight = true;
	//facingLeft = false;
	//animations spritesheet
	

	

	//arena_blocks[0].setFillColor(sf::Color(100, 250, 50));
	//arena_blocks[0].setSize(sf::Vector2f(100, 50));
	//arena_blocks[0].setPosition(900, 450);

}

void Player::initialize(std::string avatarIndex,sf::Vector2f startingCoordinate)
{
	animations[int(AnimationIndex::flyingright)] = Animation(0, 152, 95, 150, "right",avatarIndex);
	animations[int(AnimationIndex::flyingleft)] = Animation(0, 152, 95, 150, "left", avatarIndex);
	animations[int(AnimationIndex::walkingright)] = Animation(0, 0, 95, 150, "right", avatarIndex);
	animations[int(AnimationIndex::walkingleft)] = Animation(0, 0, 95, 150, "left", avatarIndex);
	animations[int(AnimationIndex::standingright)] = Animation(0, 0, 95, 150, "stillright", avatarIndex);
	animations[int(AnimationIndex::standingleft)] = Animation(0, 167, 95, 150, "stillleft", avatarIndex);
	lhand.loadFromFile("pic/avatar/a" + avatarIndex + "lefthand1.png");
	rhand.loadFromFile("pic/avatar/a" + avatarIndex + "righthand.png");//animations[int(AnimationIndex::standing)] = Animation(0, 0, 95, 150, "left", noKeyWasPressed);

	playerHandLeft.setTexture(lhand);
	playerHandRight.setTexture(rhand);
	spritePlayer.setScale(scale, scale);
	playerHandLeft.setScale(scale, scale);
	playerHandRight.setScale(scale, scale);
	coordinate = startingCoordinate;
}



void Player::update(sf::Time deltaTime,playerController userController,Player& enemy)
{
	
	this->deltaTime = deltaTime;
	this->isPressedLeft = userController.isPressedLeft;
	this->isPressedRight = userController.isPressedRight;
	this->isPressedUp = userController.isPressedUp;
	this->isLeftMouseButtonPressed = userController.isLeftMouseButtonPressed;
	this->isRightMouseButtonPressed = userController.isRightMouseButtonPressed;
	this->mousePosition = userController.mousePosition;
	//std::cout << bulletsOnRound << " / "<< totalBullets<< std::endl;

	//std::cout << mousePosition.x << "," << mousePosition.y << "||"<<mouseDirection.x << "," << mouseDirection.y << std::endl;
	isOnGround = currentVelocity.y == 0;
	noKeyWasPressed = !(isPressedLeft || isPressedRight || isPressedUp);
	if (isOnGround) {
		movePlayer(maxGroundVelocity, groundDampingConstant);
		//std::cout << "Ground" << std::endl;
		}
	else {
		movePlayer(maxAirVelocity, airDampingConstant);
		//std::cout << "Air"<< std::endl;
	}

	setBulletDir();
	//fire bullets


	if (isLeftMouseButtonPressed && bulletClock.getElapsedTime().asSeconds()>0.4f && bulletsOnRound>0 && !isReloading) {
		if (facingRight == true) {
			bullets.emplace_back(Bullet(playerHandRight.getPosition(), mouseDirection, 1000, 0.2));
			
			audioManager.playSound(PlayerFiring);
		}
		else {
			sf::Vector2f temp = playerHandLeft.getPosition();
			temp.x=playerHandLeft.getPosition().x ;
			bullets.emplace_back(Bullet(temp, mouseDirection, 1000, 0.2));
			audioManager.playSound(PlayerFiring);
		}
		bulletsOnRound--;
		bulletClock.restart();

	}
	if (isRightMouseButtonPressed && (bulletsOnRound<bulletsPerRoundMaximum) && !isReloading) {
		isReloading = true;
		audioManager.playSound(PlayerReloading);
		reloadClock.restart();
	}
		
		
		if(isReloading && reloadClock.getElapsedTime().asSeconds() > 1.f) {
			int loadingBullet = bulletsPerRoundMaximum - bulletsOnRound;
			if (totalBullets < loadingBullet) {
				bulletsOnRound += totalBullets;
				totalBullets =0;
			}
			else {
				bulletsOnRound +=loadingBullet ;
				totalBullets -= loadingBullet;
			}
			isReloading = false;
		}



		int i = 0;
		for (auto  &bullet : bullets)
		{
			bullet.update(deltaTime);
			for (auto& block : arena1->blocks) {
				if (bullet.body.getGlobalBounds().intersects(block.getGlobalBounds())) {
					bullets.erase(bullets.begin() + i);
					//std::cout << "collide" << std::endl;
					//a	delete& bullet;
					//bullet.destroy();
				}
				if (bullet.body.getGlobalBounds().intersects(enemy.body.getGlobalBounds())) {
					enemy.bulletHit(bullet.damagePoints);
				}
			}
			i++;

		}
	

	

	
	
	for (const auto &block : arena1->blocks) {
		handlePlayerCollision(block);
	}
	/*for (int i = 0; i < noOfBlocks; i++) {
		handlePlayerCollision(arena1->blocks[i]);
	}*/


	if (coordinate.y > 1200) {
		isAlive = false;
	}
}
void Player::setCoordinate(sf::Vector2f coordinate)
{
	this->coordinate = coordinate;
}
void Player::setCoordinate(float x, float y)
{
	sf::Vector2f temp;
	temp.x = x;
	temp.y = y;
	this->coordinate = temp;
}



Collider Player::getCollider()
{
	 return Collider(body); 
}



sf::Vector2f Player::getCoordinate()
{
	return this->coordinate;
}

sf::Vector2f Player::getVelocity()
{
	return this->currentVelocity;
}

float Player::interpolateVelocity(float target, float current, float dampingFactor)
{
	float increment = dampingFactor * this->deltaTime.asSeconds();
	float difference = target - current;
	if (difference >increment) {
		return current + increment;
	}
	if (difference < -increment) {
		return current - increment;
	}
	return target;

}

void Player::draw(sf::RenderWindow& window)
{
	
	//healthbox position
	healthBox.setPosition(body.getPosition().x, body.getPosition().y - 30);
	healthOutlineBox.setPosition(body.getPosition().x, body.getPosition().y - 31);
	healthOutlineBox.setFillColor(sf::Color::Black);
	healthBox.setSize(sf::Vector2f(health / 2.f, 5.f));
	//health sprite
	healthSprite.setPosition(body.getPosition().x - 15, body.getPosition().y - 33);
	//fuelBox position
	fuelBox.setPosition(body.getPosition().x, body.getPosition().y - 15);
	fuelBox.setFillColor(sf::Color::Blue);
	fuelOutlineBox.setPosition(body.getPosition().x, body.getPosition().y - 16);
	fuelOutlineBox.setFillColor(sf::Color::Black);
	fuelBox.setSize(sf::Vector2f(fuel / 20.f, 5.f));
	//fuel sprite
	fuelSprite.setPosition(body.getPosition().x - 13, body.getPosition().y - 18);

	ammoSprite.setPosition(body.getPosition().x - 15, body.getPosition().y - 50);
	for (int i = 0; i < bulletsOnRound; i++) {
		bulletSprite[i].setPosition(body.getPosition().x + i * 6, body.getPosition().y - 48);
		window.draw(bulletSprite[i]);
	}

	window.draw(fuelOutlineBox);
	window.draw(fuelBox);
	window.draw(fuelSprite);
	window.draw(ammoSprite);
	

	window.draw(healthOutlineBox);
	window.draw(healthBox);
	window.draw(healthSprite);





	for (auto& bullet : bullets)
	{
		bullet.draw(window);
	}

	if (!facingRight) {
		curAnimation = AnimationIndex::walkingleft;
		if (noKeyWasPressed)
		{
			curAnimation = AnimationIndex::standingleft;
		}
	}
	if (facingRight) {
		curAnimation = AnimationIndex::walkingright;
		if (noKeyWasPressed)
		{
			curAnimation = AnimationIndex::standingright;
		}
	}
	if (!isOnGround) {
		if (((isPressedUp ||isPressedLeft ||isPressedRight) && !facingRight)) {
			if(isPressedUp) {
				curAnimation = AnimationIndex::flyingleft;
			}
			if (fuel == 0) {
				curAnimation = AnimationIndex::standingleft;
			}
		}
		if (((isPressedUp || isPressedLeft || isPressedRight) && facingRight)) {
			
			if (isPressedUp) {
				curAnimation = AnimationIndex::flyingright;
			}
			if (fuel == 0) {
				curAnimation = AnimationIndex::standingright;
			}
		}
	}

	if (!(noKeyWasPressed)) {
		animations[int(curAnimation)].update(deltaTime);
	}
	animations[int(curAnimation)].applySprite(spritePlayer);
	//body.setFillColor(sf::Color(100, 250, 50));
	//body.setSize(sf::Vector2f(100, 150));
	//window.draw(body);

	spritePlayer.setPosition(getCoordinate().x-5, getCoordinate().y);
	window.draw(spritePlayer);

	if (!facingRight)
	{
		/*playerHandLeft.setOrigin({
			playerHandLeft.getGlobalBounds().width / 2 + playerHandLeft.getOrigin().x,
			playerHandLeft.getGlobalBounds().height / 2 + playerHandLeft.getOrigin().y
			});*/

		playerHandLeft.setOrigin(playerHandLeft.getLocalBounds().left, playerHandLeft.getLocalBounds().height / 1.5);
		playerHandLeft.setPosition(body.getPosition().x + body.getLocalBounds().width-8,
			body.getPosition().y + 30 );
		window.draw(playerHandLeft);
	}
	if (facingRight)
	{
		playerHandRight.setOrigin(playerHandRight.getLocalBounds().left, playerHandRight.getLocalBounds().height / 2.5);
		playerHandRight.setPosition(body.getPosition().x+1.2,body.getPosition().y +29);
		window.draw(playerHandRight);
	}



	


}

void Player::setArena(Arena& arena)
{
	arena1 = &arena;
}


void Player::handlePlayerCollision(sf::RectangleShape other)
{
	if (collider->checkCollision((other))) {
		if (collider->intersection.height < collider->intersection.width) {
			if (body.getGlobalBounds().top < other.getGlobalBounds().top) {
				coordinate.y -= collider->intersection.height;
				if (abs(currentVelocity.y) < 1) { currentVelocity.y = 0; }
				currentVelocity.y = -elasticConstant * currentVelocity.y;
				targetVelocity.y = 0;
			}
			else {
				coordinate.y += collider->intersection.height;
				if (abs(currentVelocity.y) < 1) { currentVelocity.y = 0; }
				currentVelocity.y = -elasticConstant * currentVelocity.y;
				targetVelocity.y = currentVelocity.y;
			}
		}

		if (collider->intersection.height > collider->intersection.width) { //horizontal collission

			if (body.getGlobalBounds().left < other.getGlobalBounds().left) {
				coordinate.x -= collider->intersection.width;
				currentVelocity.x = -elasticConstant * currentVelocity.x;
				targetVelocity.x = currentVelocity.x;
			}
			else {
				coordinate.x += collider->intersection.width;
				currentVelocity.x = -elasticConstant * currentVelocity.x;
				targetVelocity.x = currentVelocity.x;
			}
		}
		body.setPosition(coordinate);


	}
}

void Player::movePlayer(sf::Vector2f maxVelocity, float dampingConstant)
{

	if (isPressedLeft) {
		targetVelocity.x = -maxVelocity.x;

		/*facingLeft = true;
		facingRight = false;*/
	}
	else if (isPressedRight) {
		targetVelocity.x = maxVelocity.x;
		/*facingRight = true;
		facingLeft = false;*/
	}
	else {
		targetVelocity.x = 0;
	}

	if (isPressedUp) {
		if (fuel>100||(fuel>1 &&currentVelocity.y<0)) {
			targetVelocity.y -= deltaTime.asSeconds() * thrustValue;
			fuel -= thrustValue*3 * deltaTime.asSeconds();
		}
		else {
			fuel -= thrustValue * 5 * deltaTime.asSeconds();
		}

	}
	targetVelocity.y += deltaTime.asSeconds() * gravity;
	fuel += 60 * deltaTime.asSeconds();
	if (fuel > 1000) fuel = 1000;
	if (fuel < 0) fuel = 0;
	//std::cout << fuel << std::endl;

	currentVelocity.x = interpolateVelocity(targetVelocity.x, currentVelocity.x, dampingConstant);
	currentVelocity.y = interpolateVelocity(targetVelocity.y, currentVelocity.y, dampingConstant);
	coordinate.x += currentVelocity.x * 5 * deltaTime.asSeconds();
	coordinate.y += currentVelocity.y * 5 * deltaTime.asSeconds();
	//spritePlayer.move(currentVelocity.x * 5 * deltaTime.asSeconds(), currentVelocity.y * 5 * deltaTime.asSeconds());
	body.setPosition(coordinate);
	//mView.setSize(500, 500);
	//mView.setCenter(coordinate);
}




void Player::bulletHit(float damagePoints)
{
	this->health-= damagePoints*0.3;
	if (health < 0) {
		isAlive = false;
	}
}

void Player::setBulletDir()
{
	if (facingRight) {
		playerCenter = playerHandRight.getPosition();
	}
	else {
		playerCenter = playerHandLeft.getPosition();
	}

	//mousePosition = sf::Vector2f(sf::Mouse::getPosition(window));
	mouseDirection = mousePosition - playerCenter;
	mouseDirection = mouseDirection / sqrt(pow(mouseDirection.x, 2) + pow(mouseDirection.y, 2));
	float pi = 3.14159265f;
	float deg = atan2(mouseDirection.y, mouseDirection.x) * 180 / pi;


	if (facingRight)
	{
		playerHandRight.setRotation(deg);
		if (deg < -90 || deg>90)
		{
			
			facingRight = false;
		}
	}
	if (!facingRight)
	{
		playerHandLeft.setRotation(deg);
		if (!(deg < -90 || deg>90))
		{
			
			facingRight = true;
		}
	}


	

}
