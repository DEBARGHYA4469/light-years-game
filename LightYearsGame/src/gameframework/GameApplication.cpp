#include "gameframework/GameApplication.h"
#include "framework/World.h"
#include "Level/GameLevelOne.h"

ly::Application* getApplication() {
	return new ly::GameApplication();
}

namespace ly {
	GameApplication::GameApplication()
		: Application(700, 1000, "Light Years", sf::Style::Titlebar | sf::Style::Close) // bit - masked 
	{
		AssetManager::Get().SetAssetRootDir(GetResourceDir()); 
		weak<GameLevelOne> newWorld = LoadWorld<GameLevelOne>();
	}
	void GameApplication::Tick(float DeltaTime)
	{
	}
}