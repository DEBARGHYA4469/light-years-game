#pragma once 
#include "gameplay/GameStage.h"
#include "SFML/Graphics.hpp"
#include "framework/TimerManager.h"

namespace ly {
	class HexagonStage : public GameStage {
	public:
		HexagonStage(World* world);
		virtual void StartStage();
		virtual void TickStage(float DeltaTime);
	private:
		void SpawnHexagon();
		virtual void StageFinished();

		float mSpawnInterval;
		float mSideSpawnOffset;
		int mSpawnGroupAmt;
		int mCurrentSpawnCount;

		sf::Vector2f mMidSpawnLocation;
		sf::Vector2f mLeftSpawnLocation;
		sf::Vector2f mRightSpawnLocation;

		TimerHandle mSpawnTimer;
	};
};