#include "Scene.h"




void Scene::Update()
{	
	BlinkingSpikes();
	for (GameObject* const& gameObject : gameObjects)
	{
		gameObject->Update();
	}
}

void Scene::Render(sf::RenderWindow* _window)
{
	for (GameObject* const& gameObject : gameObjects)
	{
		gameObject->Render(_window);
	}
}

GameObject* Scene::CreateGameObject(const std::string& _name)
{
	auto gameObject = new GameObject();
	gameObject->SetName(_name);
	gameObjects.push_back(gameObject);
	return gameObject;
}

GameObject* Scene::CreateAnyGameObject(const std::string& name, const ObjectType& type, const sf::Vector2f& position, const sf::Color color, const sf::Vector2f& size,const SpriteStyle& style,float moveSpeed)
{
	GameObject* gameObject = CreateGameObject(name);
	gameObject->SetPosition(Maths::Vector2f(position.x, position.y));
	gameObject->SetType(type);
	gameObject->SetMoveSpeed(moveSpeed);

	SquareCollider* squareCollider = gameObject->CreateComponent<SquareCollider>();
	squareCollider->SetWidth(size.x);
	squareCollider->SetHeight(size.y);
	
	/*switch (style)
	{
	case SpriteStyle::Player:
		SpriteRenderer* spriteRenderer = gameObject->CreateComponent<SpriteRenderer>();
		spriteRenderer->SetTextureFromFile("Assets/Textures/witch_idle.png");
		spriteRenderer->SetRectSourceSprite(6, 5, 20, 38);
		spriteRenderer->SetPosSpriteXY(4, 16);
		spriteRenderer->SetSprite();
		spriteRenderer->SetScale();
		break;
	case SpriteStyle::Mushroom:
		SpriteRenderer* spriteRenderer = gameObject->CreateComponent<SpriteRenderer>();
		spriteRenderer->SetTextureFromFile("Assets/Textures/Mushroom.png");
		spriteRenderer->SetRectSourceSprite(105, 66, 83, 95);
		spriteRenderer->SetSprite();
		break;
	default:
		ShapeRenderer* shapeRenderer = gameObject->CreateComponent<ShapeRenderer>();
		shapeRenderer->SetSize(size);
		shapeRenderer->SetColor(color);
		break;
	}*/

	if (SpriteStyle::Player == style) {
		SpriteRenderer* spriteRenderer = gameObject->CreateComponent<SpriteRenderer>();
		spriteRenderer->SetupPlayer();
		spriteRenderer->SetPosSpriteXY(4, 16);
		spriteRenderer->SetSprite(spriteRenderer->GetTexture(), spriteRenderer->GetRectSourceSprite());
	}
	else if (SpriteStyle::Mushroom == style) {
		SpriteRenderer* spriteRenderer = gameObject->CreateComponent<SpriteRenderer>();
		spriteRenderer->SetTextureFromFile("Assets/Textures/Mushroom.png");
		spriteRenderer->SetRectSourceSprite(105, 66, 83, 95,RectType::Idle);
		spriteRenderer->SetSprite(spriteRenderer->GetTexture(),spriteRenderer->GetRectSourceSprite());
		spriteRenderer->SetScale(sf::Vector2f(0.5f, 0.5f));
	}
	else if (SpriteStyle::Spikes == style) {
		SpriteRenderer* spriteRenderer = gameObject->CreateComponent<SpriteRenderer>();
		spriteRenderer->SetTextureFromFile("Assets/Textures/spikes.png");
		spriteRenderer->SetRectSourceSprite(0, 0, 128, 128, RectType::Idle);
		spriteRenderer->SetSprite(spriteRenderer->GetTexture(), spriteRenderer->GetRectSourceSprite());
		spriteRenderer->SetScale(sf::Vector2f(0.4f, 0.4f));
	}
	else if (SpriteStyle::Hibiscus == style) {
		SpriteRenderer* spriteRenderer = gameObject->CreateComponent<SpriteRenderer>();
		spriteRenderer->SetTextureFromFile("Assets/Textures/flower_sheet.png");
		spriteRenderer->SetRectSourceSprite(326, 268, 35, 45, RectType::Idle);
		spriteRenderer->SetSprite(spriteRenderer->GetTexture(), spriteRenderer->GetRectSourceSprite());
		
	}
	else if (SpriteStyle::Wolf == style) {
		SpriteRenderer* spriteRenderer = gameObject->CreateComponent<SpriteRenderer>();
		spriteRenderer->SetTextureFromFile("Assets/Textures/wolf.png");
		spriteRenderer->SetRectSourceSprite(5, 1, 22, 60, RectType::Idle);
		spriteRenderer->SetSprite(spriteRenderer->GetTexture(), spriteRenderer->GetRectSourceSprite());
		spriteRenderer->SetScale(sf::Vector2f(1.2f, 1.2f));

	}
	
	else {
		ShapeRenderer* shapeRenderer = gameObject->CreateComponent<ShapeRenderer>();
		shapeRenderer->SetSize(size);
		shapeRenderer->SetColor(color);
	}


	if (ObjectType::Player == type || ObjectType::Table == type)
	{
		Inventory* inventory = gameObject->CreateComponent<Inventory>();
	}
	else if (ObjectType::Enemy == type) {
		Waypoint* waypoint = gameObject->CreateComponent<Waypoint>();
	}

	return gameObject;
}

std::vector<GameObject*> Scene::GetGameObjectType(ObjectType _type) {
	std::vector<GameObject*> res;
	for (GameObject* gameObject : gameObjects) {
		if (gameObject->GetType() == _type) {
			res.push_back(gameObject);
		}
	}
	return res;
}

void Scene::BlinkingSpikes() {
	sf::Time currentTime = GlobalClock::getGlobalClock().getElapsedTime();
	sf::Time timeElapsed = currentTime - startTimer;
	std::vector<GameObject*> listSpikes =GetGameObjectType(ObjectType::Spikes);
	for (GameObject* spike : listSpikes) {
		if (timeElapsed > sf::seconds(0.5f)) {
			if (spike->isEnabled()) {
				spike->setEnabled(false);
			}
			else {
				spike->setEnabled(true);
			}
			startTimer = currentTime;
		}
	}


}

std::vector<GameObject*> Scene::CreateAllGameObjects() {
	std::vector<GameObject*> importantGameObjects;

	CreateAnyGameObject("Mushroom", ObjectType::Ressource, sf::Vector2f(3650.f, 250.f), sf::Color::White, sf::Vector2f(41, 47.f), SpriteStyle::Mushroom);
	CreateAnyGameObject("Mushroom", ObjectType::Ressource, sf::Vector2f(450.f, 2800.f), sf::Color::White, sf::Vector2f(41, 47.f), SpriteStyle::Mushroom);
	CreateAnyGameObject("Hibiscus", ObjectType::Ressource, sf::Vector2f(1200.f, 400.f), sf::Color::Magenta, sf::Vector2f(40, 40.f), SpriteStyle::Hibiscus);
	CreateAnyGameObject("Hibiscus", ObjectType::Ressource, sf::Vector2f(300.f, 1100.f), sf::Color::Magenta, sf::Vector2f(40, 40.f), SpriteStyle::Hibiscus);
	CreateAnyGameObject("Hibiscus", ObjectType::Ressource, sf::Vector2f(2600.f, 1300.f), sf::Color::Magenta, sf::Vector2f(40, 40.f), SpriteStyle::Hibiscus);
	CreateAnyGameObject("Spikes", ObjectType::Spikes, sf::Vector2f(1700.f, 550.f), sf::Color::Green, sf::Vector2f(40, 40.f), SpriteStyle::Spikes);
	CreateAnyGameObject("Spikes", ObjectType::Spikes, sf::Vector2f(1700.f, 500.f), sf::Color::Green, sf::Vector2f(40, 40.f), SpriteStyle::Spikes);
	CreateAnyGameObject("Spikes", ObjectType::Spikes, sf::Vector2f(1850.f, 550.f), sf::Color::Green, sf::Vector2f(40, 40.f), SpriteStyle::Spikes);
	CreateAnyGameObject("Spikes", ObjectType::Spikes, sf::Vector2f(1850.f, 500.f), sf::Color::Green, sf::Vector2f(40, 40.f), SpriteStyle::Spikes);
	CreateAnyGameObject("Spikes", ObjectType::Spikes, sf::Vector2f(2000.f, 550.f), sf::Color::Green, sf::Vector2f(40, 40.f), SpriteStyle::Spikes);
	CreateAnyGameObject("Spikes", ObjectType::Spikes, sf::Vector2f(2000.f, 500.f), sf::Color::Green, sf::Vector2f(40, 40.f), SpriteStyle::Spikes);

	//Zone avec table de craft
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(0.f, 0.f), sf::Color::Blue, sf::Vector2f(600.f, 50.f), SpriteStyle::Wall);
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(0.f, 550.f), sf::Color::Blue, sf::Vector2f(600.f, 50.f), SpriteStyle::Wall);
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(0.f, 0.f), sf::Color::Blue, sf::Vector2f(50.f, 600.f), SpriteStyle::Wall);
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(550.f, 0.f), sf::Color::Blue, sf::Vector2f(50.f, 225.f), SpriteStyle::Wall);
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(550.f, 350.f), sf::Color::Blue, sf::Vector2f(50.f, 225.f), SpriteStyle::Wall);

	//Couloir 1
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(550.f, 350), sf::Color::Blue, sf::Vector2f(400.f, 50.f), SpriteStyle::Wall);
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(550.f, 175.f), sf::Color::Blue, sf::Vector2f(400.f, 50.f), SpriteStyle::Wall);

	//Salle 1
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(950.f, 0.f), sf::Color::Blue, sf::Vector2f(800.f, 50.f), SpriteStyle::Wall);
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(950.f, 800.f), sf::Color::Blue, sf::Vector2f(325.f, 50.f), SpriteStyle::Wall);
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(1425.f, 800.f), sf::Color::Blue, sf::Vector2f(325.f, 50.f), SpriteStyle::Wall);
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(950.f, 0.f), sf::Color::Blue, sf::Vector2f(50.f, 225.f), SpriteStyle::Wall);
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(950.f, 350.f), sf::Color::Blue, sf::Vector2f(50.f, 450.f), SpriteStyle::Wall);
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(1700.f, 0.f), sf::Color::Blue, sf::Vector2f(50.f, 450.f), SpriteStyle::Wall);
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(1700.f, 625.f), sf::Color::Blue, sf::Vector2f(50.f, 225.f), SpriteStyle::Wall);

	//Couloir 2
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(1225.f, 800.f), sf::Color::Blue, sf::Vector2f(50.f, 200.f), SpriteStyle::Wall);
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(1375.f, 800.f), sf::Color::Blue, sf::Vector2f(50.f, 400.f), SpriteStyle::Wall);
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(775.f, 1150.f), sf::Color::Blue, sf::Vector2f(650.f, 50.f), SpriteStyle::Wall);
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(775.f, 1000.f), sf::Color::Blue, sf::Vector2f(500.f, 50.f), SpriteStyle::Wall);

	//Salle 2
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(0.f, 800.f), sf::Color::Blue, sf::Vector2f(800.f, 50.f), SpriteStyle::Wall);
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(0.f, 1350.f), sf::Color::Blue, sf::Vector2f(800.f, 50.f), SpriteStyle::Wall);
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(750.f, 800.f), sf::Color::Blue, sf::Vector2f(50.f, 250.f), SpriteStyle::Wall);
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(750.f, 1150.f), sf::Color::Blue, sf::Vector2f(50.f, 250.f), SpriteStyle::Wall);
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(0.f, 800.f), sf::Color::Blue, sf::Vector2f(50.f, 600.f), SpriteStyle::Wall);

	//Couloir 3
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(1700.f, 450.f), sf::Color::Blue, sf::Vector2f(400.f, 50.f), SpriteStyle::Wall);
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(1700.f, 600.f), sf::Color::Blue, sf::Vector2f(400.f, 50.f), SpriteStyle::Wall);

	//Salle 3
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(2100.f, 200.f), sf::Color::Blue, sf::Vector2f(600.f, 50.f), SpriteStyle::Wall);
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(2100.f, 850.f), sf::Color::Blue, sf::Vector2f(600.f, 50.f), SpriteStyle::Wall);
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(2100.f, 200.f), sf::Color::Blue, sf::Vector2f(50.f, 300.f), SpriteStyle::Wall);
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(2100.f, 600.f), sf::Color::Blue, sf::Vector2f(50.f, 300.f), SpriteStyle::Wall);
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(2700.f, 200.f), sf::Color::Blue, sf::Vector2f(50.f, 300.f), SpriteStyle::Wall);
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(2700.f, 600.f), sf::Color::Blue, sf::Vector2f(50.f, 300.f), SpriteStyle::Wall);

	//Couloir 4
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(2700.f, 450.f), sf::Color::Blue, sf::Vector2f(400.f, 50.f), SpriteStyle::Wall);
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(2700.f, 600.f), sf::Color::Blue, sf::Vector2f(400.f, 50.f), SpriteStyle::Wall);

	//Salle 4
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(3100.f, 200.f), sf::Color::Blue, sf::Vector2f(600.f, 50.f), SpriteStyle::Wall);
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(3100.f, 850.f), sf::Color::Blue, sf::Vector2f(250.f, 50.f), SpriteStyle::Wall);
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(3500.f, 850.f), sf::Color::Blue, sf::Vector2f(250.f, 50.f), SpriteStyle::Wall);
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(3700.f, 200.f), sf::Color::Blue, sf::Vector2f(50.f, 700.f), SpriteStyle::Wall);
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(3100.f, 200.f), sf::Color::Blue, sf::Vector2f(50.f, 300.f), SpriteStyle::Wall);
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(3100.f, 600.f), sf::Color::Blue, sf::Vector2f(50.f, 300.f), SpriteStyle::Wall);

	//Couloir 5
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(3350.f, 850.f), sf::Color::Blue, sf::Vector2f(50.f, 200.f), SpriteStyle::Wall);
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(3500.f, 850.f), sf::Color::Blue, sf::Vector2f(50.f, 400.f), SpriteStyle::Wall);
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(3000.f, 1050.f), sf::Color::Blue, sf::Vector2f(400.f, 50.f), SpriteStyle::Wall);
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(3000.f, 1200.f), sf::Color::Blue, sf::Vector2f(550.f, 50.f), SpriteStyle::Wall);

	//Salle 5
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(2200.f, 1050.f), sf::Color::Blue, sf::Vector2f(800.f, 50.f), SpriteStyle::Wall);
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(2200.f, 1650.f), sf::Color::Blue, sf::Vector2f(200.f, 50.f), SpriteStyle::Wall);
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(2500.f, 1650.f), sf::Color::Blue, sf::Vector2f(550.f, 50.f), SpriteStyle::Wall);
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(3000.f, 1250.f), sf::Color::Blue, sf::Vector2f(50.f, 300.f), SpriteStyle::Wall);
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(2200.f, 1200.f), sf::Color::Blue, sf::Vector2f(50.f, 500.f), SpriteStyle::Wall);

	//Couloir 6
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(3000.f, 1500.f), sf::Color::Blue, sf::Vector2f(400.f, 50.f), SpriteStyle::Wall);
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(3000.f, 1650.f), sf::Color::Blue, sf::Vector2f(200.f, 50.f), SpriteStyle::Wall);
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(3350.f, 1500.f), sf::Color::Blue, sf::Vector2f(50.f, 400.f), SpriteStyle::Wall);
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(3200.f, 1650.f), sf::Color::Blue, sf::Vector2f(50.f, 250.f), SpriteStyle::Wall);

	//Salle 6
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(3000.f, 1850.f), sf::Color::Blue, sf::Vector2f(200.f, 50.f), SpriteStyle::Wall);
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(3400.f, 1850.f), sf::Color::Blue, sf::Vector2f(400.f, 50.f), SpriteStyle::Wall);
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(3000.f, 2450.f), sf::Color::Blue, sf::Vector2f(850.f, 50.f), SpriteStyle::Wall);
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(3000.f, 1850.f), sf::Color::Blue, sf::Vector2f(50.f, 600.f), SpriteStyle::Wall);
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(3800.f, 1850.f), sf::Color::Blue, sf::Vector2f(50.f, 600.f), SpriteStyle::Wall);

	//Couloir 7
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(2350.f, 1650.f), sf::Color::Blue, sf::Vector2f(50.f, 400.f), SpriteStyle::Wall);
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(2500.f, 1650.f), sf::Color::Blue, sf::Vector2f(50.f, 400.f), SpriteStyle::Wall);

	//Salle 7
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(2200.f, 2000.f), sf::Color::Blue, sf::Vector2f(200.f, 50.f), SpriteStyle::Wall);
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(2500.f, 2000.f), sf::Color::Blue, sf::Vector2f(200.f, 50.f), SpriteStyle::Wall);
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(2150.f, 2000.f), sf::Color::Blue, sf::Vector2f(50.f, 800.f), SpriteStyle::Wall);
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(2700.f, 2000.f), sf::Color::Blue, sf::Vector2f(50.f, 800.f), SpriteStyle::Wall);
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(2200.f, 2750.f), sf::Color::Blue, sf::Vector2f(200.f, 50.f), SpriteStyle::Wall);
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(2500.f, 2750.f), sf::Color::Blue, sf::Vector2f(200.f, 50.f), SpriteStyle::Wall);

	//Couloir 8
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(2350.f, 2750.f), sf::Color::Blue, sf::Vector2f(50.f, 200.f), SpriteStyle::Wall);
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(2500.f, 2750.f), sf::Color::Blue, sf::Vector2f(50.f, 200.f), SpriteStyle::Wall);

	//Salle 8
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(2200.f, 2950.f), sf::Color::Blue, sf::Vector2f(200.f, 50.f), SpriteStyle::Wall);
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(2500.f, 2950.f), sf::Color::Blue, sf::Vector2f(200.f, 50.f), SpriteStyle::Wall);
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(2150.f, 2950.f), sf::Color::Blue, sf::Vector2f(50.f, 400.f), SpriteStyle::Wall);
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(2700.f, 2950.f), sf::Color::Blue, sf::Vector2f(50.f, 400.f), SpriteStyle::Wall);
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(2150.f, 3350.f), sf::Color::Blue, sf::Vector2f(600.f, 50.f), SpriteStyle::Wall);

	//Couloir 9
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(1600.f, 1050.f), sf::Color::Blue, sf::Vector2f(600.f, 50.f), SpriteStyle::Wall);
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(1800.f, 1200.f), sf::Color::Blue, sf::Vector2f(400.f, 50.f), SpriteStyle::Wall);
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(1600.f, 1050.f), sf::Color::Blue, sf::Vector2f(50.f, 400.f), SpriteStyle::Wall);
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(1750.f, 1200.f), sf::Color::Blue, sf::Vector2f(50.f, 250.f), SpriteStyle::Wall);

	//Salle 9
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(1400.f, 1400.f), sf::Color::Blue, sf::Vector2f(200.f, 50.f), SpriteStyle::Wall);
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(1800.f, 1400.f), sf::Color::Blue, sf::Vector2f(200.f, 50.f), SpriteStyle::Wall);
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(2000.f, 1400.f), sf::Color::Blue, sf::Vector2f(50.f, 600.f), SpriteStyle::Wall);
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(1400.f, 1950.f), sf::Color::Blue, sf::Vector2f(250.f, 50.f), SpriteStyle::Wall);
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(1750.f, 1950.f), sf::Color::Blue, sf::Vector2f(250.f, 50.f), SpriteStyle::Wall);
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(1400.f, 1400.f), sf::Color::Blue, sf::Vector2f(50.f, 250.f), SpriteStyle::Wall);
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(1400.f, 1750.f), sf::Color::Blue, sf::Vector2f(50.f, 250.f), SpriteStyle::Wall);

	//Couloir 10
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(1600.f, 1950.f), sf::Color::Blue, sf::Vector2f(50.f, 200.f), SpriteStyle::Wall);
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(1750.f, 1950.f), sf::Color::Blue, sf::Vector2f(50.f, 200.f), SpriteStyle::Wall);

	//Salle 10
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(1400.f, 2100.f), sf::Color::Blue, sf::Vector2f(200.f, 50.f), SpriteStyle::Wall);
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(1800.f, 2100.f), sf::Color::Blue, sf::Vector2f(200.f, 50.f), SpriteStyle::Wall);
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(1400.f, 2150.f), sf::Color::Blue, sf::Vector2f(50.f, 400.f), SpriteStyle::Wall);
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(1950.f, 2150.f), sf::Color::Blue, sf::Vector2f(50.f, 400.f), SpriteStyle::Wall);
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(1400.f, 2500.f), sf::Color::Blue, sf::Vector2f(600.f, 50.f), SpriteStyle::Wall);

	//Couloir 11
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(800.f, 1600.f), sf::Color::Blue, sf::Vector2f(600.f, 50.f), SpriteStyle::Wall);
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(800.f, 1750.f), sf::Color::Blue, sf::Vector2f(600.f, 50.f), SpriteStyle::Wall);

	//Salle 11
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(0.f, 1600.f), sf::Color::Blue, sf::Vector2f(800.f, 50.f), SpriteStyle::Wall);
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(0.f, 1600.f), sf::Color::Blue, sf::Vector2f(50.f, 600.f), SpriteStyle::Wall);
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(800.f, 1800.f), sf::Color::Blue, sf::Vector2f(50.f, 400.f), SpriteStyle::Wall);
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(0.f, 2200.f), sf::Color::Blue, sf::Vector2f(400.f, 50.f), SpriteStyle::Wall);
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(525.f, 2200.f), sf::Color::Blue, sf::Vector2f(325.f, 50.f), SpriteStyle::Wall);

	//Couloir 12
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(350.f, 2200.f), sf::Color::Blue, sf::Vector2f(50.f, 400.f), SpriteStyle::Wall);
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(525.f, 2200.f), sf::Color::Blue, sf::Vector2f(50.f, 400.f), SpriteStyle::Wall);

	//Salle 12
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(150.f, 2550.f), sf::Color::Blue, sf::Vector2f(200.f, 50.f), SpriteStyle::Wall);
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(575.f, 2550.f), sf::Color::Blue, sf::Vector2f(200.f, 50.f), SpriteStyle::Wall);
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(150.f, 2550.f), sf::Color::Blue, sf::Vector2f(50.f, 600.f), SpriteStyle::Wall);
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(750.f, 2550.f), sf::Color::Blue, sf::Vector2f(50.f, 600.f), SpriteStyle::Wall);
	CreateAnyGameObject("Wall", ObjectType::Wall, sf::Vector2f(150.f, 3100.f), sf::Color::Blue, sf::Vector2f(600.f, 50.f), SpriteStyle::Wall);

	GameObject* table = CreateAnyGameObject("Table", ObjectType::Table, sf::Vector2f(200.f, 100.f), sf::Color::Cyan, sf::Vector2f(150.f, 80.f), SpriteStyle::Wall);
	GameObject* enemy1 = CreateAnyGameObject("Enemy", ObjectType::Enemy, sf::Vector2f(1100.f, 500.f), sf::Color::Yellow, sf::Vector2f(30.f, 50.f), SpriteStyle::Wolf,200.f);
	GameObject* enemy2 = CreateAnyGameObject("Enemy", ObjectType::Enemy, sf::Vector2f(3600.f, 250.f), sf::Color::Yellow, sf::Vector2f(50.f, 600.f), SpriteStyle::Wall, 200.f);
	GameObject* enemy3 = CreateAnyGameObject("Enemy", ObjectType::Enemy, sf::Vector2f(350.f, 2550.f), sf::Color::Yellow, sf::Vector2f(100.f, 150.f), SpriteStyle::Wall, 200.f);
	GameObject* enemy4 = CreateAnyGameObject("Enemy", ObjectType::Enemy, sf::Vector2f(475.f, 2200.f), sf::Color::Yellow, sf::Vector2f(100.f, 150.f), SpriteStyle::Wall, 200.f);
	GameObject* enemy5 = CreateAnyGameObject("Enemy", ObjectType::Enemy, sf::Vector2f(900.f, 1300.f), sf::Color::Yellow, sf::Vector2f(100.f, 150.f), SpriteStyle::Wall, 200.f);
	GameObject* enemy6 = CreateAnyGameObject("Enemy", ObjectType::Enemy, sf::Vector2f(1050.f, 2050.f), sf::Color::Yellow, sf::Vector2f(100.f, 150.f), SpriteStyle::Wall, 200.f);
	GameObject* enemy7 = CreateAnyGameObject("Enemy", ObjectType::Enemy, sf::Vector2f(1200.f, 1300.f), sf::Color::Yellow, sf::Vector2f(100.f, 150.f), SpriteStyle::Wall, 200.f);
	GameObject* enemy8 = CreateAnyGameObject("Enemy", ObjectType::Enemy, sf::Vector2f(0.f, 750.f), sf::Color::Yellow, sf::Vector2f(100.f, 300.f), SpriteStyle::Wall, 200.f);
	GameObject* player = CreateAnyGameObject("Player", ObjectType::Player, sf::Vector2f(400.f, 400.f), sf::Color::Red, sf::Vector2f(27.f, 55.f), SpriteStyle::Player,800.f);

	importantGameObjects.push_back(player); 
	importantGameObjects.push_back(table);
	importantGameObjects.push_back(enemy1);
	importantGameObjects.push_back(enemy2);
	importantGameObjects.push_back(enemy3);
	importantGameObjects.push_back(enemy4);
	importantGameObjects.push_back(enemy5);
	importantGameObjects.push_back(enemy6);
	importantGameObjects.push_back(enemy7);
	importantGameObjects.push_back(enemy8);

	enemy1->GetComponent<Waypoint>()->AddWaypoint(Maths::Vector2f(1100.f, 600.f));
	enemy1->GetComponent<Waypoint>()->AddWaypoint(Maths::Vector2f(1100.f, 300.f));

	enemy2->GetComponent<Waypoint>()->AddWaypoint(Maths::Vector2f(3600.f, 250.f));
	enemy2->GetComponent<Waypoint>()->AddWaypoint(Maths::Vector2f(3200.f, 250.f));

	enemy3->GetComponent<Waypoint>()->AddWaypoint(Maths::Vector2f(350.f, 2550.f));
	enemy3->GetComponent<Waypoint>()->AddWaypoint(Maths::Vector2f(200.f, 2550.f));
	enemy3->GetComponent<Waypoint>()->AddWaypoint(Maths::Vector2f(200.f, 2200.f));
	enemy3->GetComponent<Waypoint>()->AddWaypoint(Maths::Vector2f(350.f, 2200.f));

	enemy4->GetComponent<Waypoint>()->AddWaypoint(Maths::Vector2f(475.f, 2200.f));
	enemy4->GetComponent<Waypoint>()->AddWaypoint(Maths::Vector2f(625.f, 2200.f));
	enemy4->GetComponent<Waypoint>()->AddWaypoint(Maths::Vector2f(625.f, 2550.f));
	enemy4->GetComponent<Waypoint>()->AddWaypoint(Maths::Vector2f(475.f, 2550.f));

	enemy5->GetComponent<Waypoint>()->AddWaypoint(Maths::Vector2f(900.f, 1300.f));
	enemy5->GetComponent<Waypoint>()->AddWaypoint(Maths::Vector2f(900.f, 2050.f));

	enemy6->GetComponent<Waypoint>()->AddWaypoint(Maths::Vector2f(1050.f, 2050.f));
	enemy6->GetComponent<Waypoint>()->AddWaypoint(Maths::Vector2f(1050.f, 1300.f));

	enemy7->GetComponent<Waypoint>()->AddWaypoint(Maths::Vector2f(1200.f, 1300.f));
	enemy7->GetComponent<Waypoint>()->AddWaypoint(Maths::Vector2f(1200.f, 2050.f));

	enemy8->GetComponent<Waypoint>()->AddWaypoint(Maths::Vector2f(0.f, 700.f));
	enemy8->GetComponent<Waypoint>()->AddWaypoint(Maths::Vector2f(0.f, 1100.f));
	enemy8->GetComponent<Waypoint>()->AddWaypoint(Maths::Vector2f(700.f, 1100.f));
	enemy8->GetComponent<Waypoint>()->AddWaypoint(Maths::Vector2f(700.f, 700.f));


	table->GetComponent<Inventory>()->AddItem("Hibiscus", 3.f);
	table->GetComponent<Inventory>()->AddItem("Mushroom", 2.f);

	return importantGameObjects;
}

