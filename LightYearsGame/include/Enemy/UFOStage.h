#pragma once 
#include "gameplay/GameStage.h"
#include "SFML/Graphics.hpp"
#include "framework/TimerManager.h"

namespace ly {
	class UFOStage : public GameStage {
	public:
		UFOStage(World *world);
		virtual void StartStage();
		virtual void TickStage(float DeltaTime);
	private:
		sf::Vector2f GetRandomSpawnLocation() const;
		virtual void StageFinished();
		void SpawnUFO();
		int mSpawnAmount;
		float mSpawnInterval;
		int mCurrentSpawnAmount;
		float mUFOSpeed;
		TimerHandle mSpawnTimer;
	};
};
