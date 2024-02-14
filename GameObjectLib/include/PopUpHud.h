#pragma once 

#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "GlobalClock.h"

enum class PopUpType
{
    QuestHud,
    PopUp,
    Inventory,
    Leaderboard,
};
class PopUpHud
{
public:
    PopUpHud(float x, float y, PopUpType _type);

    ~PopUpHud() = default;

    void Update(std::string string);
    void Render(sf::RenderWindow* _window);
    void SetEnabled(bool _bool) { enabled = _bool; }
    bool IsEnabled() { return enabled; }
    void SetColor(sf::Color _color) { hudText->setFillColor(_color); }
private:
    const sf::Time showDuration = sf::seconds(2.0);
    PopUpType type;
    bool enabled = true;
    sf::Time startTimer = sf::Time::Zero;
    sf::Text* hudText = nullptr;
    sf::Font hudFont;
};