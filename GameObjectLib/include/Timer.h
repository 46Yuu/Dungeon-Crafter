#pragma once
#include <SFML/Graphics.hpp>
#include "GlobalClock.h"
#include <iostream>

class Timer
{
public:
	Timer();
	~Timer() = default;
	std::string sfTimeToString(sf::Time time);
	void Update();
	sf::Text* GetHudText() { return hudText; }
	void Render(sf::RenderWindow* _window) {_window->draw(*hudText); }
	void SetPause(bool _bool);
	sf::Time GetActualTimer() { return actualTimer; }
	void ResetTimer(){startGame = GlobalClock::getGlobalClock().getElapsedTime();}
private:
	bool enabled = true;
	bool paused = false;
	sf::Time pauseTime = sf::Time::Zero;
	sf::Time startGame = sf::Time::Zero;
	sf::Time actualTimer = sf::Time::Zero;
	sf::Text* hudText = nullptr;
	sf::Font hudFont;
};