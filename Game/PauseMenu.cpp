#include "PauseMenu.h"

PauseMenu::PauseMenu(sf::RenderWindow* _window) {
    window = _window;
    window->setFramerateLimit(144);
    SetupHud();

}

void PauseMenu::Render() {
    window->clear();
    Update();
    window->draw(resumeOption);
    window->draw(exitOption);
    window->display();
}

void PauseMenu::Update() {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
    if (resumeOption.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
        resumeOption.setFillColor(sf::Color::Red);
    }
    else {
        resumeOption.setFillColor(sf::Color::White);
    }
    if (exitOption.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
        exitOption.setFillColor(sf::Color::Red);
    }
    else {
        exitOption.setFillColor(sf::Color::White);
    }

}


void PauseMenu::SetupHud() {
    if (!font.loadFromFile("Assets/Textures/pixelated.ttf")) {
        std::cout << "Couldn't load Assets/Textures/pixelated.ttf";
    }

    resumeOption = sf::Text("Resume", font, 50);
    resumeOption.setPosition(350, 200);
    resumeOption.setFillColor(sf::Color::White);
    window->draw(resumeOption);


    exitOption = sf::Text("Exit", font, 50);
    exitOption.setPosition(350, 300);
    exitOption.setFillColor(sf::Color::White);
    window->draw(exitOption);


}

PauseOptionType PauseMenu::HandleInput(sf::Event event) {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
    if (resumeOption.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
            return PauseOptionType::Resume;
        }
    }
    else if (exitOption.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
            return PauseOptionType::Exit;
        }
    }
    return PauseOptionType::Default;
}