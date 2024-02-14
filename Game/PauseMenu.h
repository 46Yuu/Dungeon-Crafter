#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

enum class PauseOptionType {
	Resume,
	Exit,
	Default,
};


class PauseMenu {
public:
	PauseMenu(sf::RenderWindow* _window);
	~PauseMenu() = default;

	void SetupHud();
	void Render();
	void Update();
	sf::RenderWindow* GetWindow() { return window; }
	PauseOptionType HandleInput(sf::Event event);
private:
	sf::RenderWindow* window = nullptr;
	sf::Font font;
	sf::Text resumeOption;
	sf::Text exitOption;
};