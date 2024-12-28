#pragma once 
#include "gameplay/GameStage.h"

namespace ly {
	class WaitStage : public GameStage {
	public:
		WaitStage(World *world, float waitDuration = 4.f);
		virtual void StartStage() override;
		virtual void TickStage(float DeltaTime) override;
	private:
		float mWaitDuration;
	};
}