#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

#include "Component.h"

class SquareCollider : public Component
{
public:
	SquareCollider() = default;
	~SquareCollider() override = default;

	float width = 50.0f;
	float height = 50.0f;

	float GetWidth() const { return width; }
	float GetHeight() const { return height; }

	void SetWidth(const float _width) { width = _width; }
	void SetHeight(const float _height) { height = _height; }

	void SetSize(const float _width, const float _height) { width = _width; height = _height; }

	static bool IsColliding(const SquareCollider& _colliderA, const SquareCollider& _colliderB ,bool colliderIsEnabled);

	void Update() override;

	bool isEnabled() { return enabled; }

private: 
	bool enabled = true;
};
