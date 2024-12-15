#include "gameframework/GameApplication.h"
#include "framework/World.h"
#include "framework/Actor.h"

ly::Application* getApplication() {
	return new ly::GameApplication();
}

namespace ly {
	GameApplication::GameApplication()
		: Application(700, 700, "Light Years", sf::Style::Titlebar | sf::Style::Close) // bit - masked 
	{
		weak<World> newWorld = LoadWorld<World>();
		newWorld.lock()->SpawnActor<Actor>();
		actorToDestroy = newWorld.lock()->SpawnActor<Actor>();
		actorToDestroy.lock()->setTexture(GetResourceDir()+"SpaceShooterRedux/PNG/playerShip3_orange.png");
		counter = 0;
	}
	void GameApplication::Tick(float DeltaTime)
	{
		counter += DeltaTime;
		if (counter > 2.f) {
			if (!actorToDestroy.expired()) {
				actorToDestroy.lock()->Destroy();
			}
		}
	}
}