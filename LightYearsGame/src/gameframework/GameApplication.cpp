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
		newWorld.lock()->SpawnActor<Actor>();
		testplayerSpaceShip = newWorld.lock()->SpawnActor<PlayerSpaceShip>();
		testplayerSpaceShip.lock()->setTexture("SpaceShooterRedux/PNG/playerShip3_orange.png");
		testplayerSpaceShip.lock()->setActorLocation(sf::Vector2f(400, 400));
		testplayerSpaceShip.lock()->setActorRotation(-90.f);
		//testplayerSpaceShip.lock()->setVelocity(sf::Vector2f(0.f, -200.f));
		//counter = 0;
	}
	void GameApplication::Tick(float DeltaTime)
	{
		counter += DeltaTime;
		if (counter > 2.f) {
			if (!testplayerSpaceShip.expired()) {
				testplayerSpaceShip.lock()->Destroy();
			}
		}
	}
}