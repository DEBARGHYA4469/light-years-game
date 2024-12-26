#pragma once 
#include <framework/Application.h>
#include <framework/Actor.h>
#include <Config.h>

namespace ly {
	class GameApplication : public Application {
	public:
		GameApplication();
		virtual void Tick(float DeltaTime) override;
	};
};