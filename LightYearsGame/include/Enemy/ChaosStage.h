#pragma once 
#include "gameplay/GameStage.h"
#include <framework/TimerManager.h>
#include <SFML/Graphics.hpp>

namespace ly {
	class ChaosStage : public GameStage {
	public:
		ChaosStage(World* world);

		virtual void StartStage() override;
		virtual void TickStage(float DeltaTime) override;
	private:
		virtual void StageFinished();
		void SpawnVanguard();
		void SpawnTwinBlade();
		void SpawnHexagon();
		void SpawnUFO();

		void IncreaseDifficulty();
		void StageDurationReached();

		float mSpawnInterval;
		float mMinSpawnInterval;
		float mSpawnIntervalDecrement;
		float mSpawnIntervalDecrementInterval;
		
		float mStageDuration;
		TimerHandle mDifficultTimerHandle; 
		TimerHandle mSpawnTimer;

		sf::Vector2f GetRandomSpawnLocationTop() const;
		sf::Vector2f GetRandomSpawnLocationSide() const;
	};
}