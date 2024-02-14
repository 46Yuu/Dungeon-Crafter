#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Timer.h"
#include "PopUpHud.h"

class Hud
{
public:
    Hud() = default;
    Hud(sf::RenderWindow* _window);
    ~Hud() = default;
    PopUpHud* GetQuestHud() { return questHud; }
    Timer* GetTimer() { return timer; }
    sf::View GetView() { return hud; }
    PopUpHud* GetPopUpHud() { return popUpHud; }
    PopUpHud* GetEndgameHud() { return endgameHud; }
    PopUpHud* GetInventoryHud() { return inventoryHud; }
    void UpdateAndRender(sf::RenderWindow* window) const;
private:
    PopUpHud* questHud = nullptr;
    Timer* timer = nullptr;
    PopUpHud* popUpHud = nullptr;
    PopUpHud* inventoryHud = nullptr;
    PopUpHud* endgameHud = nullptr;
    sf::View hud;
};