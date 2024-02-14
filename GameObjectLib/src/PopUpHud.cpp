#include "PopUpHud.h"

PopUpHud::PopUpHud(float x, float y, PopUpType _type) {
    if (!hudFont.loadFromFile("Assets/Textures/pixelated.ttf")) {
        std::cout << "File couldn't be loaded.";
    }
    hudText = new sf::Text;
    hudText->setFont(hudFont);
    hudText->setCharacterSize(40);
    hudText->setFillColor(sf::Color::White);
    hudText->setPosition(x, y);
    type = _type;
}

void PopUpHud::Update(std::string string) {
    if (PopUpType::PopUp == type) {
        startTimer = GlobalClock::getGlobalClock().getElapsedTime();
    }
    hudText->setString(string);
}

void PopUpHud::Render(sf::RenderWindow* _window) {
    if (PopUpType::PopUp == type) {
        sf::Time currentTime = GlobalClock::getGlobalClock().getElapsedTime();
        sf::Time timeElapsed = currentTime - startTimer;
        if (enabled && timeElapsed < showDuration) {
            _window->draw(*hudText);
        }
    }
    else if (enabled) _window->draw(*hudText);
}