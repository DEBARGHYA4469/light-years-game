#include "gameframework/GameApplication.h"
#include "framework/World.h"
#include "framework/Actor.h"

ly::Application* getApplication() {
	return new ly::GameApplication();
}

namespace ly {
	GameApplication::GameApplication() {
		weak<World> newWorld = LoadWorld<World>();
		newWorld.lock()->SpawnActor<Actor>();
		actorToDestroy = newWorld.lock()->SpawnActor<Actor>();
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