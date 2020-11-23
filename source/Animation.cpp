#include "Animation.h"


Animation::Animation()
{
}

Animation::Animation(int startingX, int startingY, int width, int height, std::string dir, std::string avatarIndex)
{

	if (dir == "left")
	{
		texture.loadFromFile("pic/avatar/a" + avatarIndex + "leftview.png");
		for (int i = 0; i < nFrames; i++)
		{
			frames[i] = { startingX + i * width,startingY,width,startingY + height };
		}
	}
	if (dir == "right")
	{
		texture.loadFromFile("pic/avatar/a" + avatarIndex + "rightview.png");
		for (int i = 0; i < nFrames; i++)
		{
			frames[i] = { startingX + i * width,startingY,width,startingY + height };
		}
	}
	if (dir == "stillright")
	{
		/*texture.loadFromFile("pic/avatar/a3standingstill.png");
		for (int i = 0; i < nFrames; i++)
		{
			frames[i] = { startingX + i * width,startingY,width,startingY + height };
		}*/
		texture.loadFromFile("pic/avatar/a" + avatarIndex + "standing.png");
		for (int i = 0; i < nFrames; i++)
		{
			frames[i] = { startingX + i * width,startingY,width,startingY + height };
		}
	}
	if (dir == "stillleft")
	{
		texture.loadFromFile("pic/avatar/a" + avatarIndex + "standing.png");
		for (int i = 0; i < nFrames; i++)
		{
			frames[i] = { startingX + i * width,startingY,width,startingY + height };
		}
	}
}


void Animation::applySprite(sf::Sprite& s)const
{
	s.setTexture(texture);
	s.setTextureRect(frames[iFrame]);
}

void Animation::update(sf::Time dt)
{
	time += 20 * dt.asSeconds();
	while (time >= holdTime)
	{
		time -= holdTime;
		nxtUpdate();
	}
}

void Animation::nxtUpdate()
{
	if (++iFrame >= nFrames)
	{
		iFrame = 0;
	}
}




