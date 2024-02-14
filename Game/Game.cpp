#include "Game.h"

Game::Game() {

    importantGameObjects = scene.CreateAllGameObjects();

    window = new sf::RenderWindow(sf::VideoMode(1600, 900), "SFML Engine");
    camera = new Camera(window);
    window->setFramerateLimit(144);
    save = new Saves;
    achievement.Update(AchievementType::GamePlayed);
    audioManager.Setup();
    hud = new Hud(window);
    mainMenu = new MainMenu(window);
    pauseMenu = new PauseMenu(window);
}


void Game::StartGame() {
    while (window->isOpen())
    {
        sf::Event event;
        sf::Time previousTime = GlobalClock::getGlobalClock().getElapsedTime();
        switch (currentGameState)
        {
        case GameState::MainMenu:
            mainMenu->Render();
            
            while (window->pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window->close();
                }
                OptionType optionChoosed = mainMenu->HandleInput(event);
                switch (optionChoosed)
                {
                case OptionType::Play:
                    hud->GetTimer()->ResetTimer();
                    currentGameState = GameState::Playing; 
                    break;
                case OptionType::Settings:
                    break;
                case OptionType::Exit:
                    window->close();
                    break;
                case OptionType::Default:
                    break;
                default:
                    break;
                }
            }
            break;
        case GameState::Playing:
            Play();
            break;
        case GameState::Pause:
             pauseMenu->Render();

            while (window->pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window->close();
                }
                PauseOptionType optionChoosed = pauseMenu->HandleInput(event);
                switch (optionChoosed)
                {
                case PauseOptionType::Resume:
                    inputManager.SetPaused(false);
                    currentGameState = GameState::Playing;
                    break;

                case PauseOptionType::Exit:
                    window->close();
                    break;
                case PauseOptionType::Default:
                    break;
                default:
                    break;
                }
            }
            break;
        default:
            break;
        }
    }

}

void Game::Play() {
    hud->GetTimer()->SetPause(false);
    sf::Time currentTime = GlobalClock::getGlobalClock().getElapsedTime();
    sf::Time deltaTime = currentTime - previousTime;
    previousTime = currentTime;


    sf::Event event;

    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window->close();
        inputManager.ProcessInput(event);

    }

    physicsManager.UpdatePlayer(importantGameObjects.at(0), inputManager.IsMovingRight(), inputManager.IsMovingLeft(), inputManager.IsMovingUp(), inputManager.IsMovingDown());
    GameObject* collidedWith = collisionManager.PlayerInCollisionWith(importantGameObjects.at(0), scene);
    bool isColliding = collisionManager.HandleCollisions(importantGameObjects.at(0), scene, inputManager, collidedWith, camera, audioManager, hud, save);
    physicsManager.MovePlayer(importantGameObjects.at(0), deltaTime, isColliding);
    physicsManager.UpdateAllEnemies(scene.GetGameObjectType(ObjectType::Enemy), deltaTime);

    if (inputManager.IsPaused()) {
        hud->GetTimer()->SetPause(true);
        currentGameState = GameState::Pause;
    }

    window->clear(sf::Color::Black);
    camera->Update(importantGameObjects.at(0));
    window->setView(camera->GetCamera());
    scene.Update();
    scene.Render(window);

    window->setView(hud->GetView());
    hud->UpdateAndRender(window);
    window->display();
    
}