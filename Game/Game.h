#pragma once
#include <SFML/Graphics.hpp>


#include "GameObject.h"
#include "Scene.h"
#include "SquareCollider.h"
#include "InputManager.h"
#include "PhysicsManager.h"
#include "CollisionManager.h"
#include "GlobalClock.h"
#include "Camera.h"
#include "AudioManager.h"
#include "Timer.h"
#include "Hud.h"
#include "Saves.h"
#include "Achievements.h"
#include "MainMenu.h"
#include "PauseMenu.h"

enum class GameState {
    MainMenu,
    Playing,
    Pause,
};

class Game
{
public:
    Game();
    ~Game() = default;
    void StartGame();
    void Play();

    sf::RenderWindow* GetWindow() { return window; }
    std::vector<GameObject*> GetImportantGameObjects() { return importantGameObjects; }
    Camera* GetCamera() { return camera; }
    InputManager GetInputManager() { return inputManager; }
    PhysicsManager GetPhysicsManager() { return physicsManager; }
    CollisionManager GetCollisionManager() { return collisionManager; }
    AudioManager GetAudioManager() { return audioManager; }
    Saves* GetSaves() { return save; }
    Achievements GetAchievements() { return achievement; }
    Hud* GetHud() { return hud; }
    sf::Time GetPreviousTime() { return previousTime; }
private:
    GameState currentGameState = GameState::MainMenu;
    Scene scene;
    std::vector<GameObject*> importantGameObjects;
    sf::RenderWindow* window = nullptr;
    Camera* camera = nullptr;
    InputManager inputManager;
    PhysicsManager physicsManager;
    CollisionManager collisionManager;
    AudioManager audioManager;
    Saves* save = nullptr;
    Achievements achievement;
    Hud* hud = nullptr;
    sf::Time previousTime = sf::Time::Zero;

    MainMenu* mainMenu = nullptr;
    PauseMenu* pauseMenu = nullptr;
};