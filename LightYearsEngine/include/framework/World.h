#pragma once 
#include "framework/Core.h"
#include "SFML/Graphics.hpp"

namespace ly {

	class Actor;
	class Application;
	class World {
	public:
		World(Application* owningApp);
		void BeginPlayInternal();
		void tickInternal(float deltaTime);
		void Render(sf::RenderWindow& window);
		virtual ~World();

		template<typename ActorType> weak<ActorType> SpawnActor() {
			shared<ActorType> newActor{ new ActorType(this, "")};
			mpendingActors.push_back(newActor);
			return newActor;
		}

		sf::Vector2u getWindowSize() const;

	private:

		virtual void tick(float deltaTime);
		virtual void BeginPlay();

		Application* mowningApp;
		bool mBeganPlay;

		List<shared<Actor>> mActors;
		List<shared<Actor>> mpendingActors;
	};
}