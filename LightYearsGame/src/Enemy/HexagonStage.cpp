#include "Enemy/HexagonStage.h"
#include "Enemy/Hexagon.h"
#include "framework/World.h"
#include "framework/TimerManager.h"

namespace ly {
	HexagonStage::HexagonStage(World* world)
	:GameStage(world),
		mSpawnInterval{3.f},
		mSideSpawnOffset{80.f},
		mSpawnGroupAmt{3},
		mCurrentSpawnCount{0},
		mMidSpawnLocation{ world->getWindowSize().x / 2.f, -100.f},
		mRightSpawnLocation{ world->getWindowSize().x / 2.f + mSideSpawnOffset, -100.f - mSideSpawnOffset},
		mLeftSpawnLocation{ world->getWindowSize().x / 2.f - mSideSpawnOffset, -100.f - mSideSpawnOffset }
	{	

	}
	void HexagonStage::StartStage()
	{
		mSpawnTimer = TimerManager::Get().SetTimer(GetWeakRef(), &HexagonStage::SpawnHexagon, mSpawnInterval, true);
	}
	void HexagonStage::TickStage(float DeltaTime)
	{
	}
	void HexagonStage::SpawnHexagon()
	{
		weak<Hexagon> newHexagon = GetWorld()->SpawnActor<Hexagon>();
		newHexagon.lock()->SetActorLocation(mMidSpawnLocation);
		newHexagon.lock()->SetActorRotation(90.f);
		newHexagon = GetWorld()->SpawnActor<Hexagon>();
		newHexagon.lock()->SetActorLocation(mLeftSpawnLocation);
		newHexagon.lock()->SetActorRotation(90.f);
		newHexagon = GetWorld()->SpawnActor<Hexagon>();
		newHexagon.lock()->SetActorLocation(mRightSpawnLocation);
		newHexagon.lock()->SetActorRotation(90.f);

		if (++mCurrentSpawnCount == mSpawnGroupAmt) {
			FinishStage();
		}
	}
	void HexagonStage::StageFinished()
	{
		TimerManager::Get().ClearTimer(mSpawnTimer);
	}
};