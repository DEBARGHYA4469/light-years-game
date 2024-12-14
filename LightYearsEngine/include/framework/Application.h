#pragma once
#include "SFML/Graphics.hpp"
#include "framework/Core.h"

namespace ly {

	class World;

	class Application {
	public:
		Application();
		void run();
		template <typename WorldType>
		weak<WorldType> LoadWorld();
	private:

		void TickInternal(float DeltaTime);
		void RenderInternal();
		virtual void Render();
		virtual void Tick(float DeltaTime);

		sf::RenderWindow mWindow;
		float mTargetframeRate;
		sf::Clock mTickClock;

		shared<World> currentWorld;
	};

	template<typename WorldType>
	inline weak<WorldType> Application::LoadWorld()
	{
		shared<WorldType> newWorld { new WorldType(this) };
		currentWorld = newWorld;
		return newWorld;
	}
};