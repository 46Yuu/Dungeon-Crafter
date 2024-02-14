#include "InputManager.h"

void InputManager::ProcessInput(sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
        case sf::Keyboard::D:
            isMovingRight = true;
            break;
        case sf::Keyboard::Q:
            isMovingLeft = true;
            break;
        case sf::Keyboard::Z:
            isMovingUp = true;
            break;
        case sf::Keyboard::S:
            isMovingDown = true;
            break;
        case sf::Keyboard::E:
            if (!isInteracting) {
                isInteracting = true;
                startPressedTime = GlobalClock::getGlobalClock().getElapsedTime();
            }
            break;
        case sf::Keyboard::Escape:
            isGamePaused = true;
            break;
        }
    }
    else if (event.type == sf::Event::KeyReleased) {
        switch (event.key.code) {
        case sf::Keyboard::D:
            isMovingRight = false;
            break;
        case sf::Keyboard::Q:
            isMovingLeft = false;
            break;
        case sf::Keyboard::Z:
            isMovingUp = false;
            break;
        case sf::Keyboard::S:
            isMovingDown = false;
            break;
        case sf::Keyboard::E:
            isInteracting = false;
            break;
        }
    }
}

   
