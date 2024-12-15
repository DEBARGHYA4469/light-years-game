#pragma once
#include "SFML/Graphics.hpp"
#include "framework/Core.h"

namespace ly {

	class World;

	class Application {
	public:
		Application(unsigned int windowWidth, unsigned int windowHeight, const std::string& title, sf::Uint32 style);
		void run();
		template <typename WorldType>
		weak<WorldType> LoadWorld(); // weak pointer, if world gets deleted client is notified.

		/*
			World is a entity on its own. Application holds a reference to a world. 
			But any other client need not hold a shared ptr to World. It can request weak ptr from Application. 
			Meaning if the World ceases to exist, any other application widget should not prolong its lifetime. 
		*/

		sf::Vector2u GetWindowSize () const;
	private:

		void TickInternal(float DeltaTime);
		void RenderInternal();
		virtual void Render();
		virtual void Tick(float DeltaTime);

		sf::RenderWindow mWindow;
		float mTargetframeRate;
		sf::Clock mTickClock;

		shared<World> currentWorld;
		sf::Clock mCleanCycleClock;
		float mCleanCycleInterval;
	};

	template<typename WorldType>
	inline weak<WorldType> Application::LoadWorld()
	{
		shared<WorldType> newWorld { new WorldType(this) };
		currentWorld = newWorld;
		return newWorld;
	}
};