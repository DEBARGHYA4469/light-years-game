#pragma once 
#include "framework/Object.h"
#include "framework/Delegate.h"

namespace ly {
	class World;
	// Requirement : Game Stage should support Delegates and Timers.
	class GameStage : public Object {
	public:
		GameStage(World* world);
		const World* GetWorld() const { return mWorld; }
		World* GetWorld() { return mWorld; }

		Delegate<> OnStageFinished;

		virtual void StartStage();
		virtual void TickStage(float DeltaTime);
		void FinishStage();
		bool IsStageFinished() const { return mStageFinished;  }
	private:	
		World* mWorld;
		bool mStageFinished;
		virtual void StageFinished();
	};
};