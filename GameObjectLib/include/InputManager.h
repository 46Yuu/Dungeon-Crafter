#pragma once

#include <SFML/Graphics.hpp>
#include "GlobalClock.h"


class InputManager
{
private:
    bool isMovingRight = false;
    bool isMovingLeft = false;
    bool isMovingUp = false;
    bool isMovingDown = false;
    bool isInteracting = false;
    bool isGamePaused = false;
public: 
    void ProcessInput(sf::Event& event);
    bool IsMovingRight() { return isMovingRight; }
    bool IsMovingLeft() { return isMovingLeft; }
    bool IsMovingUp() { return isMovingUp; }
    bool IsMovingDown() { return isMovingDown; }
    bool IsInteracting() { return isInteracting; }
    bool IsPaused() {return isGamePaused;}
    void SetPaused(bool _bool) { isGamePaused = _bool; }
    sf::Time startPressedTime = GlobalClock::getGlobalClock().getElapsedTime();
};