#pragma once 
#include "framework/World.h"
#include "framework/TimerManager.h"

namespace ly {
	class Actor;
	class PlayerSpaceShip;
	class GamePlayHUD;
	class GameLevelOne : public World {
	public:
		GameLevelOne(Application* app); 
	private:
		virtual void BeginPlay() override;
		void PlayerSpaceShipDestroyed(Actor* destroyed);
		weak<PlayerSpaceShip> mPlayerSpaceShip;
		weak<GamePlayHUD> mGamePlayHUD;
		virtual void InitGameStages() override;
		void GameOver();
	};
};