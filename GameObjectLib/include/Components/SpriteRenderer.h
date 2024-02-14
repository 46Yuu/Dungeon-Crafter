#include <SFML/Graphics.hpp>
#include "Component.h"
#include "GlobalClock.h"
#include <iostream>

enum class SpriteStyle
{
	Player,
	Mushroom,
	Spikes,
	Hibiscus,
	Wolf,
	Wall,
};

enum class RectType
{
	Idle,
	IdleLeft,
	Movement,
	Death,
};

class SpriteRenderer : public Component
{
public:
	SpriteRenderer();
	~SpriteRenderer() override;

	void SetupPlayer();
	void SetTextureFromFile(std::string filePath);
	void SetTextureFromIntRect() { sprite->setTextureRect(rectSourceSprite); }
	void SetIdleRightTexture() { sprite->setTexture(*texture); }
	void SetIdleLeftTexture() { sprite->setTexture(*textureLeft); }
	void SetMovementRightTexture() { sprite->setTexture(*textureMovementRight);}
	void SetMovementLeftTexture() { sprite->setTexture(*textureMovementLeft); }
	void SetDeathTexture() { sprite->setTexture(*textureDeath); SetRectSourceSprite(4, 1, 23, 38, RectType::Death);}
	void SetRectSourceSprite(float left, float top, float width, float height, RectType rect);
	void SetSprite(sf::Texture* texture,sf::IntRect rect) {sprite = new sf::Sprite(*texture, rect);}
	void SetScale(sf::Vector2f scale);
	void SetPosSpriteXY(float _x, float _y) { xSprite = _x; ySprite = _y; }
	void Render(sf::RenderWindow* _window) override;
	void Update();
	sf::IntRect GetRectSourceSprite() { return rectSourceSprite; }
	sf::Texture* GetTexture() { return texture; }
	bool GetIsDying() { return isDying; }
	void SetIsDying(bool _bool) { isDying = _bool; }
	void SetFacingLeft(bool _bool) { facingLeft = _bool; }
	bool GetFacingLeft() { return facingLeft; }

private:
	float xSprite = 0;
	float ySprite = 0;
	bool player = false;
	bool isDying = false;
	bool facingLeft = false;
	sf::Texture* texture;
	sf::Texture* textureLeft = nullptr;
	sf::IntRect rectSourceSprite;

	sf::Texture* textureMovementRight = nullptr;
	sf::Texture* textureMovementLeft = nullptr;
	sf::Texture* textureDeath = nullptr;
	sf::Time start = sf::Time::Zero;
	sf::Time delayBetweenTexture = sf::seconds(0.100f);
	sf::IntRect rectMovementSprite;
	sf::IntRect rectDeathSprite;

	
	sf::Sprite* sprite = new sf::Sprite;
};