

#pragma once

#include <SFML/Audio.hpp>
#include <string>
#include <map>

enum AudioId {
	PlayerFiring,PlayerReloading,PlayerWalking,Theme,emptyBullet
	,TotalAudio
};


class Audio

{

private:

	Audio& operator=(Audio) = delete;

	Audio(Audio&) = delete;



	bool playBgMusic = true;

	sf::Music bgMusic;

	std::map<AudioId, sf::SoundBuffer> soundBuffers;

	sf::Sound* sounds;

	int soundCount = 0;

	int maxSoundCount = 100;

	float volume = 5.f;



public:

	//Create a audio object wherever needed

	Audio(int);

	~Audio();

	//Loading takes time so use accoringly

	//Maybe write different functions for different screens

	//so we can load audios separately

	void load(AudioId, std::string);

	void loadMenu();

	void setBgMusicStatus(bool);

	sf::Sound& playSound(AudioId);

};