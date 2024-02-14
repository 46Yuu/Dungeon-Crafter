#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

enum class OptionType{
	Play,
	Settings,
	Exit,
	Default,
};

class MainMenu
{
public:
	MainMenu(sf::RenderWindow* _window);
	~MainMenu() = default;
	void SetupHud();
	void Render();
	void Update();
	sf::RenderWindow* GetWindow() { return window; }
	
	OptionType HandleInput(sf::Event event);
private:
	sf::RenderWindow* window = nullptr;
	sf::Font font;
	sf::Text playOption;
	sf::Text settingsOption;
	sf::Text exitOption;
};