#include "AudioManager.h"


void AudioManager::Setup() {
	ressourceSound->loadFromFile("Assets/Sounds/pickup.flac");
	deathSound->loadFromFile("Assets/Sounds/death.flac");
	SetupMusic();
}

void AudioManager::SetupMusic() {
	music->openFromFile("Assets/Sounds/music.flac");
	music->setLoop(true);
	music->setVolume(30.f);
	music->play();
}


void AudioManager::SetSoundBuffer(sf::SoundBuffer* _buffer){
	sound.stop();
	sound.setBuffer(*_buffer); 
}

void AudioManager::PlayRessourceGet() {
	SetSoundBuffer(ressourceSound);
	sound.setVolume(40.f);
	sound.play();
}

void AudioManager::PlayDeathSound() {
	SetSoundBuffer(deathSound);
	sound.setVolume(80.f);
	sound.play();
}