#include "gameplay/GameStage.h"
#include "framework/Core.h"

ly::GameStage::GameStage(World* world): mWorld(world), mStageFinished(false)
{

}

void ly::GameStage::StartStage()
{
	
}

void ly::GameStage::TickStage(float DeltaTime)
{
	
}

void ly::GameStage::FinishStage()
{
	mStageFinished = true;
	StageFinished();
	OnStageFinished.BroadCast();
}

void ly::GameStage::StageFinished()
{
	
}
