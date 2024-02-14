#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>


#include "GameObject.h"
#include "Components/ShapeRenderer.h"
#include "Components/SquareCollider.h"
#include "Components/Inventory.h"
#include "Components/Waypoint.h"
#include "Components/SpriteRenderer.h"
#include "GlobalClock.h"


class Scene
{ 
public:
	Scene() = default;
	virtual ~Scene() = default;

	void Update();
	void Render(sf::RenderWindow* _window);

	GameObject* CreateGameObject(const std::string& _name);

	GameObject* CreateAnyGameObject(const std::string& name, const ObjectType& type, const sf::Vector2f& position, const sf::Color color, const sf::Vector2f& size, const SpriteStyle& style,float moveSpeed=0.f);

	std::vector<GameObject*> GetGameObjects() { return gameObjects; }

	std::vector<GameObject*> GetGameObjectType(ObjectType _type);

	std::vector<GameObject*> CreateAllGameObjects();

	void BlinkingSpikes();

private:

	sf::Time startTimer = GlobalClock::getGlobalClock().getElapsedTime();
	std::vector<GameObject*> gameObjects;
};

