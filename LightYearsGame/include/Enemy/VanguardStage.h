#pragma once 
#include <gameplay/GameStage.h>
#include "SFML/Graphics.hpp"
#include <framework/TimerManager.h>

namespace ly {
	class VanguardStage : public GameStage {
	public:
		VanguardStage(World* world);
		virtual void StartStage() override;
	private:
		float mSpawnInterval;
		float mSwitchInterval;
		float mSpawnDistanceToEdge;

		sf::Vector2f mLeftSpawnLocation;
		sf::Vector2f mRightSpawnLocation;
		sf::Vector2f mSpawnLocation;

		TimerHandle mSpawnTimerHandle;
		TimerHandle mSwitchTimerHandle;

		int mRowToSpawn;
		int mRowSpawnCount;
		int mVanguardPerRow;
		int mCurrentRowVanguardCount;

		virtual void StageFinished() override;
		void SpawnVanguard();
		void SwitchRow();
	};
};