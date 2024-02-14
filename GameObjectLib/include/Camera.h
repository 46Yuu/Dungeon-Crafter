#pragma once
#include <SFML/Graphics.hpp>
#include "Maths/Vector2.h"
#include "GameObject.h"
#include "GlobalClock.h"


class Camera
{
public:
	Camera() = default;
	Camera(sf::RenderWindow* _window);
	~Camera() = default;

	sf::View GetCamera() { return camera; }

	void SetZoomLevel(float _zoomLevel) { zoomLevel = _zoomLevel; }

	void Update(GameObject* player);

	void UpdateZoom() { camera.zoom(zoomLevel); }

	float GetZoomLevel() { return zoomLevel; }

private:
	sf::View camera;
	float zoomLevel;
	float cameraFollowSpeed = 0.03f;
};