#pragma once
#include <SFML/Graphics.hpp>
#include "Maths/Vector2.h"
#include "GameObject.h"
#include "InputManager.h"
#include "CollisionManager.h"
#include <iostream>

class PhysicsManager {
private:
    float acceleration = 0.1f;
    float deceleration = 0.08f;
    float maxVelocity = 0.4f;
    Maths::Vector2f velocity{ 0, 0 };

public:
    void UpdatePlayer(GameObject* _player, bool _isMovingRight, bool _isMovingLeft, bool _isMovingUp, bool _isMovingDown);
    void MovePlayer(GameObject* _player, sf::Time _deltaTime, bool isColliding);
    void UpdateEnemy(GameObject* enemy, sf::Time _deltaTime);
    void UpdateAllEnemies(std::vector<GameObject*> enemies, sf::Time _deltaTime);

    Maths::Vector2f getVelocity() { return velocity; }
    float getAcceleration() { return acceleration; }
    float getDeceleration() { return deceleration; }
    float getMaxVelocity() { return maxVelocity; }
    void setVelocity(const Maths::Vector2f& _vector) { velocity.X = _vector.X; velocity.Y = _vector.Y; }
    void setVelocityX(float _x) { velocity.X = _x; }
    void setVelocityY(float _y) { velocity.Y = _y; }



};