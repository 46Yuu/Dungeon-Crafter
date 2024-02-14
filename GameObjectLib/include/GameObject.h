#pragma once
#include <string>
#include <vector>

#include "Components/Item.h"
#include "Maths/Vector2.h"
#include "Components/Component.h"

class Component;

enum class ObjectType
{
	Player,
	Wall,
	Ressource,
	Table,
	Spikes,
	Enemy,
	Default,
};

class GameObject
{
public:
	GameObject() = default;
	virtual ~GameObject() = default;

	std::string GetName() const { return name; }
	ObjectType GetType() const { return type; }
	Maths::Vector2<float> GetPosition() const { return position; }

	void SetName(const std::string& _name) { name = _name; }
	void SetPosition(const Maths::Vector2<float>& _position) { position = _position; }
	void SetType(const ObjectType& _type) { type = _type; }
	void SetMoveSpeed(float _movespeed) { moveSpeed = _movespeed; }

	float GetMoveSpeed() { return moveSpeed; }
	bool isEnabled() { return enabled; }

	void setEnabled(const bool _status) { enabled = _status; }

	void AddComponent(Component* _component);

	template<typename T>
	T* CreateComponent();

	template<typename T>
	T* GetComponent(); 

	void RemoveComponent(Component* _component);
	void Update() const;
	void Render(sf::RenderWindow* _window) const;

private:
	float moveSpeed = 0.f;
	std::string name = "GameObject";
	ObjectType type = ObjectType::Default;
	bool enabled = true;
	Maths::Vector2<float> position = Maths::Vector2f::zero();
	std::vector<Component*> components;
};

#include "GameObject.inl"