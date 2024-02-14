#include "Camera.h"

Camera::Camera(sf::RenderWindow* window) {
    camera = window->getDefaultView();
    zoomLevel = 0.7f;
    camera.zoom(zoomLevel);
}

void Camera::Update(GameObject* player) {
    Maths::Vector2f cameraCenter = Maths::Vector2f(camera.getCenter().x, camera.getCenter().y);
    Maths::Vector2f targetCameraPosition = Maths::Vector2f::lerp(player->GetPosition(), cameraCenter, 0.01f);
    sf::Vector2f targetCameraPos = sf::Vector2f(targetCameraPosition.X, targetCameraPosition.Y);
    sf::Vector2f cameraOffset = targetCameraPos - camera.getCenter();
    camera.move(cameraFollowSpeed * cameraOffset);
}
