#pragma once 
#include "framework/World.h"
#include "framework/TimerManager.h"

namespace ly {
	class PlayerSpaceShip;
	class GameLevelOne : public World {
	public:
		GameLevelOne(Application* app); 
	private:
		virtual void BeginPlay() override;
		weak<PlayerSpaceShip> testplayerSpaceShip;
		virtual void InitGameStages() override;
	};
};