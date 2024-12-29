#pragma once 
#include <framework/Object.h>
#include <framework/Delegate.h>
#include <player/PlayerSpaceShip.h>
#include <spaceship/SpaceShip.h>

namespace ly {
	class Player : public Object {
	public:
		Player();
		weak<PlayerSpaceShip> SpawnSpaceShip(World* world);
		weak<PlayerSpaceShip> GetCurrentSpaceShip() const { return mCurrentPlayerSpaceShip; }
		void AddLifeCount(unsigned int Amt);
		int GetLifeCount() const { return mPlayerLifeCount; }
		int AddScore(unsigned int Amt);
		int GetScore() const { return mScore; }

		Delegate<int> onLifeChanged;
		Delegate<int> onScoreChanged;
		Delegate<> onLifeExhausted;

	private:
		unsigned int mPlayerLifeCount;
		unsigned int mScore;
		weak<PlayerSpaceShip> mCurrentPlayerSpaceShip;
	};
};