#pragma once 
#include "Enemy/TwinBlade.h"
#include "gameplay/GameStage.h"
#include "framework/TimerManager.h"

namespace ly {
	class TwinBladeStage : public GameStage {
	public:
		TwinBladeStage(World* world);
		virtual void StartStage() override;
	private:
		float mSpawnInterval;
		float mSwitchInterval;
		float mSpawnDistanceToCenter;

		sf::Vector2f mLeftSpawnLocation;
		sf::Vector2f mRightSpawnLocation;
		sf::Vector2f mSpawnLocation;

		TimerHandle mSpawnTimerHandle;

		int mCurrentSpawnCount;
		int mSpawnAmount;

		virtual void StageFinished() override;
		void SpawnTwinBlade();
	};
};