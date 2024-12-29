#pragma once 
#include "framework/World.h"
#include "framework/TimerManager.h"

namespace ly {
	class Actor;
	class PlayerSpaceShip;
	class GameLevelOne : public World {
	public:
		GameLevelOne(Application* app); 
	private:
		virtual void BeginPlay() override;
		void PlayerSpaceShipDestroyed(Actor* destroyed);
		weak<PlayerSpaceShip> mPlayerSpaceShip;
		virtual void InitGameStages() override;
		void GameOver();
	};
};