#include "MainMenu.h"

MainMenu::MainMenu(sf::RenderWindow* _window) {
    window = _window;
    window->setFramerateLimit(144);
    SetupHud();
   
}

void MainMenu::Render() {
    window->clear();
    Update();
    window->draw(playOption);
    window->draw(settingsOption);
    window->draw(exitOption);
    window->display();
}

void MainMenu::Update() {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
    if (playOption.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
        playOption.setFillColor(sf::Color::Red);
    }
    else {
        playOption.setFillColor(sf::Color::White);
    }
    if (settingsOption.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
        settingsOption.setFillColor(sf::Color::Red);
    }
    else {
        settingsOption.setFillColor(sf::Color::White);
    }
    if (exitOption.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
        exitOption.setFillColor(sf::Color::Red);
    }
    else {
        exitOption.setFillColor(sf::Color::White);
    }

}


void MainMenu::SetupHud() {
    if (!font.loadFromFile("Assets/Textures/pixelated.ttf")) {
        std::cout << "Couldn't load Assets/Textures/pixelated.ttf";
    }

    playOption = sf::Text("Play", font, 50);
    playOption.setPosition(350, 200);
    playOption.setFillColor(sf::Color::White);
    window->draw(playOption);

    settingsOption = sf::Text("Settings", font, 50);
    settingsOption.setPosition(350, 300);
    settingsOption.setFillColor(sf::Color::White);
    window->draw(settingsOption);

    exitOption = sf::Text("Exit", font, 50);
    exitOption.setPosition(350, 400);
    exitOption.setFillColor(sf::Color::White);
    window->draw(exitOption);


}

OptionType MainMenu::HandleInput(sf::Event event) {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
    if (playOption.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
            return OptionType::Play;
        }
    }
    else if (settingsOption.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
            return OptionType::Settings;
        }
    }
    else if (exitOption.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
            return OptionType::Exit;
        }
    }
    return OptionType::Default;
}