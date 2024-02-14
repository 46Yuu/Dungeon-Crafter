#include "Timer.h"

Timer::Timer() {
    if (!hudFont.loadFromFile("Assets/Textures/pixelated.ttf")) {
        std::cout << "File couldn't be loaded.";
    }
    hudText = new sf::Text;
    hudText->setFont(hudFont);
    hudText->setCharacterSize(50);
    hudText->setFillColor(sf::Color::White);
    hudText->setPosition(1385, 0);

    startGame = GlobalClock::getGlobalClock().getElapsedTime();
}

std::string Timer::sfTimeToString(sf::Time time) {
    int totalMilliseconds = time.asMilliseconds();
    int milliseconds = totalMilliseconds % 1000;
    int totalSeconds = totalMilliseconds / 1000;
    int seconds = totalSeconds % 60;
    int minutes = totalSeconds / 60;

    char formattedTime[10];
    std::snprintf(formattedTime, sizeof(formattedTime), "%02d:%02d:%03d", minutes, seconds, milliseconds);

    return formattedTime;
}

void Timer::Update() {
    sf::Time currentTime = GlobalClock::getGlobalClock().getElapsedTime();
    if (!paused) {
        actualTimer = currentTime - startGame;
        if (enabled) {
            hudText->setString(sfTimeToString(actualTimer));
        }
    }
}

void Timer::SetPause(bool _bool) {
    if (_bool) {
        if (!paused) {
            pauseTime = GlobalClock::getGlobalClock().getElapsedTime();
        }
    }
    else {
        if (paused) {
            sf::Time pauseDuration = GlobalClock::getGlobalClock().getElapsedTime() - pauseTime;
            startGame += pauseDuration;
        }
    }
    paused = _bool;
}