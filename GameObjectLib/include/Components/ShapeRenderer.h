#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include "SFML/Graphics/Shape.hpp"
#include "Component.h"

class ShapeRenderer : public Component
{
public:
	ShapeRenderer();
	~ShapeRenderer() override;

	void SetColor(const sf::Color& _color) { color = _color; }
	void SetSize(const sf::Vector2f & _size) { shape->setSize(_size); }

	sf::Vector2f GetSize() { return shape->getSize(); }

	void Render(sf::RenderWindow* _window) override;

	bool isEnabled() { return enabled; }

private:
	bool enabled = true;
	sf::Color color = sf::Color::White;
	sf::RectangleShape* shape = nullptr;
};
