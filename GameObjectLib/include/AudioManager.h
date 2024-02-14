#pragma once

#include <SFML/Audio.hpp>
#include <iostream>

class AudioManager
{
public:
	AudioManager() = default;
	~AudioManager() = default;

	void Setup();
	void SetupMusic();
	void SetSoundBuffer(sf::SoundBuffer* _buffer);
	void PlayRessourceGet();
	void PlayDeathSound();
	void SetDeathSoundPlayedBool(bool _bool) { deathSoundPlayed = _bool; }
	bool GetDeathSoundPlayed() { return deathSoundPlayed; }


private :
	sf::SoundBuffer* ressourceSound = new sf::SoundBuffer;
	sf::SoundBuffer* deathSound = new sf::SoundBuffer;
	bool deathSoundPlayed = false;
	sf::Music* music = new sf::Music;
	sf::Sound sound;
	
};