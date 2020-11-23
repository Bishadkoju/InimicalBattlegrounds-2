#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
class Animation
{
private:
	static constexpr int nFrames = 4;
	static constexpr float holdTime = 4.0;
	sf::Texture texture;
	sf::IntRect frames[nFrames];
	int iFrame = 0;
	float time = 0.0f;
public:
	Animation();
	Animation(int startingX, int startingY, int width, int height, std::string dir, std::string avatarIndex);
	void applySprite(sf::Sprite& s)const;
	void update(sf::Time dt);
	void nxtUpdate();
};

