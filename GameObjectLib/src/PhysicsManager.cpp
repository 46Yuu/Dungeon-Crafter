#include "PhysicsManager.h"


void PhysicsManager::UpdatePlayer(GameObject* player, bool isMovingRight, bool isMovingLeft, bool isMovingUp, bool isMovingDown) {
    Maths::Vector2f moveVector(0, 0);
    if (isMovingRight) 
        moveVector.X += 1;
    if (isMovingLeft)
        moveVector.X -= 1;
    if (isMovingUp)
        moveVector.Y -= 1;
    if (isMovingDown)
        moveVector.Y += 1;

    moveVector.normalize();

    if (moveVector.X != 0 || moveVector.Y != 0) {
        velocity.X += moveVector.X * acceleration;
        velocity.Y += moveVector.Y * acceleration;
    }
    else {
        if (std::abs(velocity.X) > deceleration)
            velocity.X -= (velocity.X > 0 ? 1 : -1) * deceleration;
        else
            velocity.X = 0;
        if (std::abs(velocity.Y) > deceleration)
            velocity.Y -= (velocity.Y > 0 ? 1 : -1) * deceleration;
        else
            velocity.Y = 0;
    }

    float velocityMagnitude = velocity.magnitude();
    if (velocityMagnitude > maxVelocity) {
        velocity.X = (velocity.X / velocityMagnitude) * maxVelocity;
        velocity.Y = (velocity.Y / velocityMagnitude) * maxVelocity;
    }

}

void PhysicsManager::MovePlayer(GameObject* _player, sf::Time _deltaTime, bool isColliding) {
    if (isColliding) {
        setVelocity(Maths::Vector2f(0.f, 0.f));
    }
    if (!_player->GetComponent<SpriteRenderer>()->GetIsDying()) {
        if (abs(velocity.getX()) > 0.f || abs(velocity.getY()) > 0.f) {
            if (velocity.getX() > 0.f) {
                if (_player->GetComponent<SpriteRenderer>()->GetFacingLeft())
                    _player->GetComponent<SpriteRenderer>()->SetFacingLeft(false);
                _player->GetComponent<SpriteRenderer>()->SetMovementRightTexture();
            }
            else if (velocity.getX() < 0.f ) {
                if (!_player->GetComponent<SpriteRenderer>()->GetFacingLeft())
                    _player->GetComponent<SpriteRenderer>()->SetFacingLeft(true);
                _player->GetComponent<SpriteRenderer>()->SetMovementLeftTexture();
            }
            
        }
        else {
            if(!_player->GetComponent<SpriteRenderer>()->GetFacingLeft())
            {
                _player->GetComponent<SpriteRenderer>()->SetIdleRightTexture();
            }
            else {
                _player->GetComponent<SpriteRenderer>()->SetIdleLeftTexture();
            }

        }
    }
    _player->SetPosition(_player->GetPosition() + velocity * _player->GetMoveSpeed() * _deltaTime.asSeconds());
    
}

void PhysicsManager::UpdateAllEnemies(std::vector<GameObject*> enemies, sf::Time _deltaTime) {
    for (GameObject* enemy : enemies) {
        UpdateEnemy(enemy, _deltaTime);
    }
}

void PhysicsManager::UpdateEnemy(GameObject* enemy, sf::Time _deltaTime) {
    if (enemy->GetComponent<Waypoint>()->GetIndex() < enemy->GetComponent<Waypoint>()->GetWaypoints().size()) {
        Maths::Vector2f waypoint = enemy->GetComponent<Waypoint>()->GetWaypoints()[enemy->GetComponent<Waypoint>()->GetIndex()];
        Maths::Vector2f direction = waypoint - enemy->GetPosition();
       
        float distance = Maths::Vector2f::distance(enemy->GetPosition(), waypoint);

        if (distance < 10.0f) {
            enemy->GetComponent<Waypoint>()->SetIndex(enemy->GetComponent<Waypoint>()->GetIndex()+1);
        }
        else {
            direction = direction / distance ;
            enemy->SetPosition(enemy->GetPosition() + direction * enemy->GetMoveSpeed() * _deltaTime.asSeconds());
        }
    }
    else {
        enemy->GetComponent<Waypoint>()->SetIndex(0);
    }
}