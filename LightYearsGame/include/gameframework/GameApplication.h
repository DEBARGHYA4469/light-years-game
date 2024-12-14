#pragma once 
#include <framework/Application.h>
#include <framework/Actor.h>

namespace ly {
	class GameApplication : public Application {
	private:
		float counter;
		weak<Actor> actorToDestroy;
	public:
		GameApplication();
		virtual void Tick(float DeltaTime) override;
	};
};