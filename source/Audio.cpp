#include "audio.h"



Audio::Audio(int maxSoundCount = 100) :maxSoundCount(maxSoundCount)

{

	sounds = new sf::Sound[maxSoundCount];

}

void Audio::load(AudioId id, std::string path) {
	sf::SoundBuffer buffer;
	buffer.loadFromFile(path.c_str());
	soundBuffers.insert(std::make_pair(id, std::move(buffer)));
}

Audio::~Audio()
{

	delete[] sounds;

}





sf::Sound& Audio::playSound(AudioId id)
{
	if (soundCount >= maxSoundCount)
		soundCount = 0;


	sounds[soundCount].setBuffer(soundBuffers[id]);

	sounds[soundCount].play();

	return sounds[soundCount++];

}



void Audio::setBgMusicStatus(bool _playBgMusic)
{
	playBgMusic = _playBgMusic;

}