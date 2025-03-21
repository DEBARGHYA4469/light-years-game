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
		void QuitApplication();
		sf::Vector2u GetWindowSize () const;
		sf::RenderWindow& GetWindow() { return mWindow; }
		const sf::RenderWindow& GetWindow() const { return mWindow; }

	private:
		bool DispatchEvent(const sf::Event& event);
		void TickInternal(float DeltaTime);
		void RenderInternal();
		virtual void Render();
		virtual void Tick(float DeltaTime);

		sf::RenderWindow mWindow;
		float mTargetframeRate;
		sf::Clock mTickClock;

		shared<World> mcurrentWorld;
		shared<World> mPendingWorld;
		sf::Clock mCleanCycleClock;
		float mCleanCycleInterval;
	};
	 
	template<typename WorldType>
	inline weak<WorldType> Application::LoadWorld()
	{
		shared<WorldType> newWorld { new WorldType(this) };
		mPendingWorld = newWorld;
		//mcurrentWorld = newWorld; // Cannot do this, iterator invalidation, because load world will be called by iterators of old world which causes old world to vanish
		// https://www.geeksforgeeks.org/iterator-invalidation-cpp/
		return newWorld;
	}
};