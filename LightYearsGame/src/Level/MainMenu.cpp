#include <Level/MainMenu.h>
#include <widgets/MainMenuHUD.h>
#include <framework/Application.h>
#include <Level/GameLevelOne.h>

ly::MainMenu::MainMenu(Application* app) : World(app)
{
	mMainMenuHUD = SpawnHUD<MainMenuHUD>();
}

void ly::MainMenu::BeginPlay()
{
	mMainMenuHUD.lock()->onStartButtonClicked.BindAction(GetWeakRef(), &ly::MainMenu::StartGame);
	mMainMenuHUD.lock()->onQuitButtonClicked.BindAction(GetWeakRef(), &ly::MainMenu::QuitGame);
}

void ly::MainMenu::InitGameStages()
{
}

void ly::MainMenu::GameOver()
{
}

void ly::MainMenu::StartGame()
{	
	GetApplication()->LoadWorld<GameLevelOne>();
}

void ly::MainMenu::QuitGame()
{
	GetApplication()->QuitApplication();
}
