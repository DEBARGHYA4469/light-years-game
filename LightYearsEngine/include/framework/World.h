#pragma once 
#include "framework/Core.h"
#include "SFML/Graphics.hpp"
#include "framework/Object.h"

namespace ly {

	class Actor;
	class Application;
	class GameStage;
	class HUD;
	class World : public Object{
	public:
		World(Application* owningApp);
		Application* GetApplication() { return mowningApp; }
		const Application* GetApplication() const { return mowningApp; }
		void BeginPlayInternal();
		void tickInternal(float deltaTime);
		void Render(sf::RenderWindow& window);
		bool DispatchEvent(const sf::Event& event);
		virtual ~World();

		template<typename ActorType, typename... Args> 
		weak<ActorType> SpawnActor(Args... args) {
			//printf("%d", this->mActors.size());
			shared<ActorType> newActor{ new ActorType(this, args...)};
			mPendingActors.push_back(newActor);
			return newActor;
		}

		template <typename HUDType, typename... Args>
		weak<HUDType> SpawnHUD(Args... args) {
			shared<HUDType> newHUD{ new HUDType(args...) };
			mHud = newHUD;
			return newHUD;
		}


		sf::Vector2u GetWindowSize() const;
		void CleanCycle();
		void AddGameStage(const shared<GameStage>& newStage);

	private:

		virtual void RenderHUD(sf::RenderWindow& window);
		virtual void tick(float deltaTime);
		virtual void BeginPlay();

		Application* mowningApp;
		bool mBeganPlay;

		List<shared<Actor>> mActors;
		List<shared<Actor>> mPendingActors;
		List<shared<GameStage>> mGameStages;
		
		shared<HUD> mHud;
		
		// Iterator to allow for list deletions
		List<shared<GameStage>>::iterator mCurrentStageIter;
		virtual void InitGameStages();
		void NextGameStage();
		void StartFirstGameStage();
		virtual void AllGameStagesFinished();
	};
}