#include "player/PlayerManager.h"

namespace ly{
	unique<PlayerManager> PlayerManager::mPlayerManager{ nullptr };

	PlayerManager& PlayerManager::Get()
	{
		if (mPlayerManager == nullptr) {
			mPlayerManager = std::move(unique<PlayerManager> {new PlayerManager()});
		}
		return *mPlayerManager;
	}

	PlayerManager::PlayerManager()
	{
	}

	Player& PlayerManager::CreateNewPlayer()
	{
		mPlayers.emplace(mPlayers.begin(), Player());
		return mPlayers.front();
	}

	Player* PlayerManager::GetPlayer(int playerIndex)
	{	
		if (playerIndex >= 0 && playerIndex <= mPlayers.size())
			return &mPlayers[playerIndex];
		return nullptr;
	}

	const Player* PlayerManager::GetPlayer(int playerIndex) const
	{
		if (playerIndex >= 0 && playerIndex <= mPlayers.size())
			return &mPlayers[playerIndex];
		return nullptr;
	}
}