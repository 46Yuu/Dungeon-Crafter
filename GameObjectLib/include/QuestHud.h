#pragma once

#include <SFML/Graphics.hpp>
#include "GlobalClock.h"
#include <iostream>
#include <string>

class QuestHud
{
public: 
	QuestHud();
	~QuestHud() = default;

	void Update(std::string string);
	void Render(sf::RenderWindow* _window) { if (enabled) _window->draw(*hudText);  }
	void SetEnabled(bool _bool) { enabled = _bool; }
private:
	bool enabled = true;
	sf::Text* hudText = nullptr;
	sf::Font hudFont;
};