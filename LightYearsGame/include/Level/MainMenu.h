#pragma once 
#include <framework/World.h>

namespace ly {
	class MainMenuHUD;
	class MainMenu : public World {
	public:
		MainMenu(Application* app);
	private:
		virtual void BeginPlay() override;
		virtual void InitGameStages() override;
		void GameOver();
		weak<MainMenuHUD> mMainMenuHUD;
		void StartGame();
		void QuitGame();
	};
};