#include "Hud.h"


Hud::Hud(sf::RenderWindow* window) {
    hud = window->getDefaultView();
    questHud = new PopUpHud(10.f, 0.f, PopUpType::QuestHud);
    popUpHud = new PopUpHud(700.f, 20.f, PopUpType::PopUp);
    inventoryHud = new PopUpHud(10.f, 700.f, PopUpType::Inventory);
    endgameHud = new PopUpHud(500.f, 20.f, PopUpType::Leaderboard);
    timer = new Timer;
    endgameHud->SetEnabled(false);
}

void Hud::UpdateAndRender(sf::RenderWindow* window) const {
    popUpHud->Render(window);
    questHud->Render(window);
    inventoryHud->Render(window);
    endgameHud->Render(window);
    timer->Update();
    timer->Render(window);
}