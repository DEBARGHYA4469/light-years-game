#pragma once 
#include <framework/Application.h>
#include <framework/Actor.h>
#include <Config.h>

namespace ly {
	class PlayerSpaceShip;
	class GameApplication : public Application {
	private:
		float counter;
		weak<PlayerSpaceShip> testplayerSpaceShip;
	public:
		GameApplication();
		virtual void Tick(float DeltaTime) override;
	};
};