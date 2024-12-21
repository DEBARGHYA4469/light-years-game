#include "gameframework/GameApplication.h"
#include "framework/World.h"
#include "framework/Actor.h"
#include <player/PlayerSpaceShip.h>
#include <framework/AssetManager.h>

ly::Application* getApplication() {
	return new ly::GameApplication();
}

namespace ly {
	GameApplication::GameApplication()
		: Application(700, 700, "Light Years", sf::Style::Titlebar | sf::Style::Close) // bit - masked 
	{
		AssetManager::Get().SetAssetRootDir(GetResourceDir()); 
		weak<World> newWorld = LoadWorld<World>();
		testplayerSpaceShip = newWorld.lock()->SpawnActor<PlayerSpaceShip>();
		testplayerSpaceShip.lock()->setTexture("SpaceShooterRedux/PNG/playerShip1_blue.png");
		testplayerSpaceShip.lock()->setActorLocation(sf::Vector2f(400, 400));
		testplayerSpaceShip.lock()->setActorRotation(0.f);

		weak<SpaceShip> testSpaceShip = newWorld.lock()->SpawnActor<SpaceShip>();
		testSpaceShip.lock()->setTexture("SpaceShooterRedux/PNG/playerShip1_orange.png");
		testSpaceShip.lock()->setActorLocation(sf::Vector2f(100, 50));
		testSpaceShip.lock()->setActorRotation(0.f);

		counter = 0.f;
	}
	void GameApplication::Tick(float DeltaTime)
	{
		counter += DeltaTime;
		if (counter > 10.f) {
			if (!testplayerSpaceShip.expired()) {
				testplayerSpaceShip.lock()->Destroy();
			}
		}
	}
}