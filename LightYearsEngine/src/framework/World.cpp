#include "framework/World.h"
#include "framework/Core.h"
#include "framework/Actor.h"
#include "framework/Application.h"
#include "gameplay/GameStage.h"

ly::World::World(Application* owningApp):
	mowningApp(owningApp),
	mBeganPlay(false),
	mActors{},
	mPendingActors{},
	mCurrentStageIter{mGameStages.end()},
	mGameStages{}
{
}

void ly::World::BeginPlayInternal()
{
	if (!mBeganPlay) {
		mBeganPlay = true;
		BeginPlay();
		InitGameStages();
		StartFirstGameStage();
	}
}

void ly::World::tickInternal(float deltaTime)
{
	for (shared<Actor> actor : mPendingActors) {
		mActors.push_back(actor);
		actor->BeginPlayInternal();
	}

	mPendingActors.clear();

	for (auto it = mActors.begin(); it != mActors.end();) {
		it->get()->TickInternal(deltaTime);
		it++;
	}

	if (mCurrentStageIter != mGameStages.end()) {
		(*mCurrentStageIter)->TickStage(deltaTime);
	}

	tick(deltaTime);
}

void ly::World::Render(sf::RenderWindow& window)
{
	for (auto actor : mActors) {
		actor->Render(window);
	}
}

ly::World::~World()
{
}

sf::Vector2u ly::World::getWindowSize() const
{
	return mowningApp->GetWindowSize();
}

void ly::World::CleanCycle()
{
	for (auto it = mActors.begin(); it != mActors.end();) {
		if (it->get()->isPendingDestroy()) {
			it = mActors.erase(it);
		}
		else {
			it++;
		}
	}
}

void ly::World::AddGameStage(const shared<GameStage>& newStage)
{
	mGameStages.push_back(newStage);
}

void ly::World::tick(float deltaTime)
{
}

void ly::World::BeginPlay()
{
}

void ly::World::InitGameStages()
{

}

void ly::World::StartFirstGameStage()
{
	mCurrentStageIter = mGameStages.begin();
	if (mCurrentStageIter != mGameStages.end()) {
		(*mCurrentStageIter)->OnStageFinished.BindAction(GetWeakRef(), &World::NextGameStage);
		(*mCurrentStageIter)->StartStage();
	}
}

void ly::World::NextGameStage()
{
	// mCurrentStageIter is not end if it reached here
	mCurrentStageIter = mGameStages.erase(mCurrentStageIter);
	if (mCurrentStageIter == mGameStages.end()) {
		AllGameStagesFinished();
		return;
	}
	(*mCurrentStageIter)->OnStageFinished.BindAction(GetWeakRef(), &World::NextGameStage);
	(*mCurrentStageIter)->StartStage();
}


void ly::World::AllGameStagesFinished()
{
	LOG("All game stages finished");
}
