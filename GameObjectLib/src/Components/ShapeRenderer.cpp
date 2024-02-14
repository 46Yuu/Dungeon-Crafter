#include "Components/ShapeRenderer.h"


ShapeRenderer::ShapeRenderer()
{
	shape = new sf::RectangleShape();
}

ShapeRenderer::~ShapeRenderer()
{
	delete shape;
	shape = nullptr;
}

void ShapeRenderer::Render(sf::RenderWindow* _window)
{
	Component::Render(_window);

	const auto position = GetOwner()->GetPosition();
	shape->setPosition(position.X, position.Y);
	shape->setFillColor(color);
	

	if (Component::GetOwner()->isEnabled()) {
		_window->draw(*shape);
	}
}
