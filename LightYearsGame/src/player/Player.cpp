#include <player/Player.h>
#include <framework/World.h>

namespace ly {
	Player::Player()
	{
		mPlayerLifeCount = 3;
		mScore = 0;
	}
	weak<PlayerSpaceShip> Player::SpawnSpaceShip(World* world)
	{
		if (mPlayerLifeCount > 0) {
			--mPlayerLifeCount;
			auto windowSize = world->GetWindowSize();
			mCurrentPlayerSpaceShip = world->SpawnActor<PlayerSpaceShip>("SpaceShooterRedux/PNG/playerShip1_blue.png");
			mCurrentPlayerSpaceShip.lock()->SetActorLocation({ windowSize.x / 2.f, windowSize.y - 100.f });
			mCurrentPlayerSpaceShip.lock()->SetActorRotation(-90.f);
			return mCurrentPlayerSpaceShip;
		}
		else {
			onLifeExhausted.BroadCast();
			return weak<PlayerSpaceShip>(); // will be expired when received
		}
		
	}
	void Player::AddLifeCount(unsigned int Amt)
	{
		if (Amt > 0) {
			mPlayerLifeCount += Amt;
			onLifeChanged.BroadCast(mPlayerLifeCount);
		}
	}
	int Player::AddScore(unsigned int Amt)
	{
		if (Amt > 0) {
			mScore += Amt;
			onScoreChanged.BroadCast(mScore);
		}
		return mScore;
	}
};