#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Scene.h"
#include "Components/SquareCollider.h"
#include "PhysicsManager.h"
#include "InputManager.h"
#include "Components/Inventory.h"
#include "Camera.h"
#include "AudioManager.h"
#include "Hud.h"
#include "iostream"
#include "GlobalClock.h"
#include "Components/ShapeRenderer.h"
#include "Timer.h"
#include "Saves.h"

class CollisionManager {

public:
    bool HandleCollisions(GameObject* player, Scene& scene, InputManager& inputManager, GameObject* collidedWith,Camera* camera,AudioManager& audioManager, Hud* hud ,Saves* saves);
    GameObject* PlayerInCollisionWith(GameObject* player, Scene& scene);
    Maths::Vector2f WallCollisionVector(GameObject* player, Maths::Vector2f wallPos, SquareCollider* collider);
    Maths::Vector2f GetPlayerPosCenter(GameObject* player);
    bool PlayerCenterCollideWithGameObject(Maths::Vector2f& playerCenterPos, SquareCollider* collider);
    void DestroyPlayerAndRespawn(GameObject* player, Camera* camera, sf::Time timeElapsed, AudioManager& audioManager);
    void InteractingRessource(sf::Time currentTime, InputManager& inputManager, GameObject* player, GameObject* ressource, AudioManager& audioManager, Hud* hud);
    std::string GetListItemsFromInventory(Inventory* questInv,std::string startString);
    std::string GetTopLeaderboard(Saves* saves);

private:
    const sf::Time interactionDuration = sf::seconds(1.0);
    bool isCollidingWithEnemy = false;
    sf::Time collisionTimer = sf::Time::Zero;
    bool isZooming = false;
    sf::Time zoomStartTime;
    float initialZoomLevel = 1.f;
    float targetZoomLevel = 1.f;
};