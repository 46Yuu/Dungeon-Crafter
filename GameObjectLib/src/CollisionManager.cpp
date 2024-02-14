#include "CollisionManager.h"



bool CollisionManager::HandleCollisions(GameObject* player, Scene& scene, InputManager& inputManager , GameObject* collidedWith, Camera* camera, AudioManager& audioManager, Hud* hud,Saves* saves) {
    SquareCollider* playerCollider = player->GetComponent<SquareCollider>();
    Maths::Vector2f playerCenterPos = GetPlayerPosCenter(player);
    for (GameObject* const& gameObject : scene.GetGameObjects()) {
        if (gameObject != player) {
            SquareCollider* collider = gameObject->GetComponent<SquareCollider>();
            if (gameObject->GetType() == ObjectType::Wall) {
                if (SquareCollider::IsColliding(*playerCollider, *collider, collider->isEnabled())) {           
                    Maths::Vector2f collisionVector = WallCollisionVector(player, gameObject->GetPosition(), collider);

                    float pushDistance = 1.0f;
                    player->SetPosition(player->GetPosition() + collisionVector * pushDistance);
                    return true;
                }
            }
            else if (gameObject->GetType() == ObjectType::Ressource && gameObject->isEnabled()) {
                sf::Time currentTime = GlobalClock::getGlobalClock().getElapsedTime();
                if (!SquareCollider::IsColliding(*playerCollider, *collider, collider->isEnabled()) && inputManager.IsInteracting() && collidedWith == nullptr) {
                    inputManager.startPressedTime = GlobalClock::getGlobalClock().getElapsedTime();
                    sf::Time timeElapsed = currentTime - inputManager.startPressedTime;
                }
                else if (SquareCollider::IsColliding(*playerCollider, *collider, collider->isEnabled()) && inputManager.IsInteracting()
                    && collidedWith->GetComponent<SquareCollider>() == collider
                    && PlayerCenterCollideWithGameObject(playerCenterPos, collider))
                    {

                    InteractingRessource(currentTime, inputManager, player, gameObject,audioManager,hud);
                    return true;
                }
            }
            else if (gameObject->GetType() == ObjectType::Table) {
                if (!SquareCollider::IsColliding(*playerCollider, *collider, collider->isEnabled())) {
                    hud->GetQuestHud()->SetEnabled(false);
                    hud->GetInventoryHud()->SetEnabled(false);
                }
                else if (SquareCollider::IsColliding(*playerCollider, *collider, collider->isEnabled())) {
                    if (inputManager.IsInteracting() && player->GetComponent<Inventory>()->CompareInventory(collider->GetOwner()->GetComponent<Inventory>())) {
                        player->GetComponent<Inventory>()->ClearInventory();
                        collider->GetOwner()->GetComponent<Inventory>()->ClearInventory();
                        hud->GetTimer()->SetPause(true);
                        sf::Time endTime = hud->GetTimer()->GetActualTimer();
                        saves->AddNewScore(endTime);
                        std::string stringLeaderboard = GetTopLeaderboard(saves);
                        std::string string = "You   finished   in   " + hud->GetTimer()->GetHudText()->getString() +"\n\n Top   5   Leaderboard   :\n" + stringLeaderboard;
                        hud->GetEndgameHud()->Update(string);
                        hud->GetEndgameHud()->SetEnabled(true);
                    }
                    else if(inputManager.IsInteracting() && !player->GetComponent<Inventory>()->CompareInventory(collider->GetOwner()->GetComponent<Inventory>())) {
                        std::string string = "Still   missing   items";
                        hud->GetPopUpHud()->Update(string);
                        hud->GetPopUpHud()->SetColor(sf::Color::Red);
                    }
                    else {
                        if (!hud->GetEndgameHud()->IsEnabled()) {
                            hud->GetQuestHud()->SetEnabled(true);
                            hud->GetInventoryHud()->SetEnabled(true);
                            hud->GetQuestHud()->Update(GetListItemsFromInventory(collider->GetOwner()->GetComponent<Inventory>(), "Needed   Items : \n"));
                            hud->GetInventoryHud()->Update(GetListItemsFromInventory(player->GetComponent<Inventory>(),"Inventory :\n"));
                        }   
                        else {
                            hud->GetQuestHud()->SetEnabled(false);
                            hud->GetInventoryHud()->SetEnabled(false);
                        }
                    }
                }
            }
            else if (gameObject->GetType() == ObjectType::Spikes || gameObject->GetType() == ObjectType::Enemy) {
                if (SquareCollider::IsColliding(*playerCollider, *collider, collider->isEnabled())) {
                    if (!isCollidingWithEnemy) {
                        isCollidingWithEnemy = true;
                        collisionTimer = GlobalClock::getGlobalClock().getElapsedTime();
                    }
                }
                sf::Time currentTime = GlobalClock::getGlobalClock().getElapsedTime();
                sf::Time timeElapsed = currentTime - collisionTimer;
                if (isCollidingWithEnemy) {
                    DestroyPlayerAndRespawn(player, camera, timeElapsed, audioManager);
                    if (timeElapsed >= interactionDuration) {
                        isCollidingWithEnemy = false;
                    }
                    return true;
                }
            }
            
        }
    }
    
    return false;
}

GameObject* CollisionManager::PlayerInCollisionWith(GameObject* player, Scene& scene) {
    SquareCollider* playerCollider = player->GetComponent<SquareCollider>();
    SquareCollider* collider;
    for (GameObject* const& gameObject : scene.GetGameObjects()) {
        if (gameObject != player) {
            collider = gameObject->GetComponent<SquareCollider>();
            if (SquareCollider::IsColliding(*playerCollider, *collider, collider->isEnabled())) {
                return collider->GetOwner();
            }
        }
    }
    return nullptr;
}

Maths::Vector2f CollisionManager::WallCollisionVector(GameObject* player, Maths::Vector2f wallPos, SquareCollider* collider) {
    Maths::Vector2f collisionVector = player->GetPosition() - wallPos;
    float length = collisionVector.magnitude();

    float playerBottom = player->GetPosition().getY() + player->GetComponent<SquareCollider>()->GetHeight();
    float playerLeft = player->GetPosition().getX();
    float playerTop = player->GetPosition().getY();
    float playerRight = player->GetPosition().getX() + player->GetComponent<SquareCollider>()->GetWidth();
    float wallBottom = collider->GetOwner()->GetPosition().getY() + collider->GetHeight();
    float wallLeft = collider->GetOwner()->GetPosition().getX();
    float wallTop = collider->GetOwner()->GetPosition().getY();
    float wallRight = collider->GetOwner()->GetPosition().getX() + collider->GetWidth();
    if (length > 0) {
        if (abs(playerBottom - wallTop) < 2.f || abs(playerTop - wallBottom) < 2.f) {
            collisionVector.X = 0.f;
            collisionVector.Y /= length;
        }
        else if (abs(playerRight - wallLeft) < 2.f || abs(playerLeft - wallRight) < 2.f) {
            collisionVector.X /= length;
            collisionVector.Y = 0.f;
        }
    }
    return collisionVector;
}

Maths::Vector2f CollisionManager::GetPlayerPosCenter(GameObject* player) {
    float playerBottom = player->GetPosition().getY() + player->GetComponent<SquareCollider>()->GetHeight();
    float playerLeft = player->GetPosition().getX();
    float playerTop = player->GetPosition().getY();
    float playerRight = player->GetPosition().getX() + player->GetComponent<SquareCollider>()->GetWidth();

    float playerCenterX = (playerRight + playerLeft)/2;
    float playerCenterY = (playerBottom + playerTop)/2;
    return Maths::Vector2f(playerCenterX, playerCenterY);
}

bool CollisionManager::PlayerCenterCollideWithGameObject(Maths::Vector2f& playerCenterPos, SquareCollider* collider) {
    float objectBottom = collider->GetOwner()->GetPosition().getY() + collider->GetHeight();
    float objectLeft = collider->GetOwner()->GetPosition().getX();
    float objectTop = collider->GetOwner()->GetPosition().getY();
    float objectRight = collider->GetOwner()->GetPosition().getX() + collider->GetWidth();
    if (playerCenterPos.X >= objectLeft && playerCenterPos.X <= objectRight &&
        playerCenterPos.Y <= objectBottom && playerCenterPos.Y >= objectTop) {
        return true;
    }
    else {
        return false;
    }
}

void CollisionManager::DestroyPlayerAndRespawn(GameObject* player, Camera* camera, sf::Time timeElapsed,AudioManager& audioManager) {
    if (timeElapsed > interactionDuration && audioManager.GetDeathSoundPlayed()) {
        player->SetPosition(Maths::Vector2f(100.f, 100.f));
        camera->SetZoomLevel(1.146f);
        camera->UpdateZoom();
        player->GetComponent<SpriteRenderer>()->SetIdleRightTexture();
        player->GetComponent<SpriteRenderer>()->SetIsDying(false);
        audioManager.SetDeathSoundPlayedBool(false);
    }
    if (!audioManager.GetDeathSoundPlayed() && timeElapsed<interactionDuration) {
        audioManager.PlayDeathSound();
        player->GetComponent<SpriteRenderer>()->SetIsDying(true);
        player->GetComponent<SpriteRenderer>()->SetDeathTexture();
        audioManager.SetDeathSoundPlayedBool(true);
    }
    //player->GetComponent<SpriteRenderer>()->
    camera->SetZoomLevel(0.999f);
    camera->UpdateZoom();
}

void CollisionManager::InteractingRessource(sf::Time currentTime,InputManager& inputManager, GameObject* player, GameObject* ressource, AudioManager& audioManager,Hud* hud) {
    sf::Time timeElapsed = currentTime - inputManager.startPressedTime;

    if (timeElapsed >= interactionDuration) {
        size_t initialSize = player->GetComponent<Inventory>()->getInventory().size();
        player->GetComponent<Inventory>()->AddItem(ressource->GetName(), 1);
        audioManager.PlayRessourceGet();
        std::string showPopUp = "+1 " + ressource->GetName();
        hud->GetPopUpHud()->SetColor(sf::Color::White);
        hud->GetPopUpHud()->Update(showPopUp);
        ressource->setEnabled(false);
        size_t currentSize = player->GetComponent<Inventory>()->getInventory().size();
        inputManager.startPressedTime = GlobalClock::getGlobalClock().getElapsedTime();
    }
}

std::string CollisionManager::GetListItemsFromInventory(Inventory* inventory,std::string startString) {
    std::vector<Item*> items = inventory->getInventory();
    std::string res = startString;
    for (Item* item : items) {
        int intValue = static_cast<int>(item->getAmount());
        res = res + item->getName() + " : " + std::to_string(intValue) + "\n";
    }
    return res;
}


std::string CollisionManager::GetTopLeaderboard(Saves* saves) {
    std::vector<std::string> leaderboard = saves->GetFormatedLeaderboard();
    std::string res;
    if (leaderboard.size() > 5) {
        for (int i = 0; i < 5; i++) {
            res = res + leaderboard.at(i)+ "\n";
        }
    }
    else {
        for (std::string score : leaderboard) {
            res = res + score + "\n";
        }
    }
    return res;
}