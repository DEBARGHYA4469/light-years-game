#pragma once 
#include "gameplay/GameStage.h"
#include "framework/Actor.h"

namespace ly {
	class BossStage : public GameStage {
	public:
		BossStage(World* world);
		virtual void StartStage() override;
	private:
		void BossDestroyed(Actor* actor);
	};
}