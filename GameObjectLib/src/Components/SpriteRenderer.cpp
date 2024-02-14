#include "Components/SpriteRenderer.h"


SpriteRenderer::SpriteRenderer() 
{
	texture = new sf::Texture;
}


SpriteRenderer::~SpriteRenderer() 
{
	delete texture;
	texture = nullptr;
}

void SpriteRenderer::SetupPlayer() {
	player = true;
	textureMovementRight = new sf::Texture;
	textureMovementLeft = new sf::Texture;
	textureDeath = new sf::Texture;
	textureLeft = new sf::Texture;

	if (!texture->loadFromFile("Assets/Textures/witch_idle_right.png"))
		std::cout << "File Assets/Textures/witch_idle.png couldn't be loaded.\n";
	if (!textureLeft->loadFromFile("Assets/Textures/witch_idle_left.png"))
		std::cout << "File Assets/Textures/witch_idle_left.png couldn't be loaded.\n";
	if (!textureMovementRight->loadFromFile("Assets/Textures/witch_run_right.png"))
		std::cout << "File Assets/Textures/witch_run_right.png couldn't be loaded.\n";
	if (!textureMovementLeft->loadFromFile("Assets/Textures/witch_run_left.png"))
		std::cout << "File Assets/Textures/witch_run_left.png couldn't be loaded.\n";
	if (!textureDeath->loadFromFile("Assets/Textures/witch_death.png"))
		std::cout << "File Assets/Textures/witch_death.png couldn't be loaded.\n";

	SetRectSourceSprite(5, 1, 20, 38, RectType::Idle);
	SetRectSourceSprite(6, 1, 19, 40, RectType::Movement);
	SetRectSourceSprite(4, 1, 23, 38, RectType::Death);
}

void SpriteRenderer::SetTextureFromFile(std::string filePath) {
	texture->loadFromFile(filePath);
}

void SpriteRenderer::Render(sf::RenderWindow* _window) {
	Component::Render(_window);

	const auto position = GetOwner()->GetPosition();
	sprite->setPosition(position.X-xSprite, position.Y-ySprite);
	

	if (Component::GetOwner()->isEnabled()) {
		_window->draw(*sprite);
	}
}

void SpriteRenderer::SetScale(sf::Vector2f scale) {
	sprite->setScale(scale);
}

void SpriteRenderer::Update() {
	if (player) {
		sf::Time currentTime = GlobalClock::getGlobalClock().getElapsedTime();
		sf::Time timeElapsed = currentTime - start;
		if (timeElapsed > delayBetweenTexture) {
			start = currentTime;
			
			if (sprite->getTexture() == texture ) {
				if (rectSourceSprite.top == 201) {
					SetRectSourceSprite(5, 1, 20, 38, RectType::Idle);
				}
				else {
					float newTop = rectSourceSprite.top + 40;
					SetRectSourceSprite(5, newTop , 20, 38, RectType::Idle);
				}
				SetSprite(texture, rectSourceSprite);
				SetScale(sf::Vector2f(2.f, 2.f));
			}
			else if (sprite->getTexture() == textureLeft) {
				if (rectSourceSprite.top == 201) {
					SetRectSourceSprite(5, 1, 20, 38, RectType::Idle);
				}
				else {
					float newTop = rectSourceSprite.top + 40;
					SetRectSourceSprite(5, newTop, 20, 38, RectType::Idle);
				}
				SetSprite(textureLeft, rectSourceSprite);
				SetScale(sf::Vector2f(2.f, 2.f));
			}
			else if (sprite->getTexture() == textureDeath) {
				if (rectDeathSprite.top == 441) {
					SetRectSourceSprite(4, 1, 23, 38, RectType::Death);
				}
				else {
					float newTop = rectDeathSprite.top + 40;
					SetRectSourceSprite(4, newTop, 23, 38, RectType::Death);
				}
				SetSprite(textureDeath, rectDeathSprite);
				SetScale(sf::Vector2f(2.f, 2.f));
			}
			else if (sprite->getTexture() == textureMovementRight) {
				if (rectMovementSprite.top == 295) {
					SetRectSourceSprite(6, 1, 19, 40, RectType::Movement);
				}
				else {
					float newTop = rectMovementSprite.top + 42;
					SetRectSourceSprite(6, newTop, 19, 40, RectType::Movement);
				}
				SetSprite(textureMovementRight, rectMovementSprite);
				SetScale(sf::Vector2f(2.f, 2.f));
			}
			else if (sprite->getTexture() == textureMovementLeft) {
				if (rectMovementSprite.top == 295) {
					SetRectSourceSprite(6, 1, 19, 40, RectType::Movement);
				}
				else {
					float newTop = rectMovementSprite.top + 42;
					SetRectSourceSprite(6, newTop, 19, 40, RectType::Movement);
				}
				SetSprite(textureMovementLeft, rectMovementSprite);
				SetScale(sf::Vector2f(2.f, 2.f));
			}
		}
	}
}


void SpriteRenderer::SetRectSourceSprite(float left, float top, float width, float height, RectType type)
{
	switch (type)
	{
	case RectType::Idle:
		rectSourceSprite = sf::IntRect(left, top, width, height);
		break;
	case RectType::Movement:
		rectMovementSprite = sf::IntRect(left, top, width, height);
		break;
	case RectType::Death:
		rectDeathSprite = sf::IntRect(left, top, width, height);
		break;
	default:

		break;
	}
	
}