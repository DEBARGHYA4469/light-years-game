#include "gameframework/GameApplication.h"
#include "framework/World.h"
#include "Level/GameLevelOne.h"
#include "Level/MainMenu.h"

ly::Application* getApplication() {
	return new ly::GameApplication();
}

namespace ly {
	GameApplication::GameApplication()
		: Application(700, 1000, "Light Years", sf::Style::Titlebar | sf::Style::Close) // bit - masked 
	{
		AssetManager::Get().SetAssetRootDir(GetResourceDir()); 
		weak<MainMenu> newWorld = LoadWorld<MainMenu>();
	}
	void GameApplication::Tick(float DeltaTime)
	{
	}
}