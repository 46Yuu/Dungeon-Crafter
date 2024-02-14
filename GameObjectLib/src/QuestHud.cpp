#include "QuestHud.h"

QuestHud::QuestHud() {
    if (!hudFont.loadFromFile("Assets/Textures/pixelated.ttf")) {
        std::cout << "File couldn't be loaded.";
    }
    hudText = new sf::Text;
    hudText->setFont(hudFont);
    hudText->setCharacterSize(40);
    hudText->setFillColor(sf::Color::White);
    hudText->setPosition(10, 0);
}

void QuestHud::Update(std::string string) {
    hudText->setString(string);
}