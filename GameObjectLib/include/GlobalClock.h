#pragma once
#include <SFML/Graphics.hpp>

class GlobalClock {
	public:
		static sf::Clock getGlobalClock() { static sf::Clock globalClock; return globalClock; }

};
	