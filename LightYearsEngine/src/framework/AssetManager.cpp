#include "framework/AssetManager.h"

namespace ly {
	unique<AssetManager> AssetManager::assetManager = nullptr;
	AssetManager& AssetManager::Get()
	{
		if (assetManager == nullptr) {
			assetManager = std::move(unique<AssetManager>{new AssetManager});
		}
		return *assetManager;
	}
	shared<sf::Texture> AssetManager::LoadTexture(const std::string& path)
	{
		auto found = mLoadedTextureMap.find(path);
		if (found != mLoadedTextureMap.end()) return found->second;
		shared<sf::Texture> newTexture{new sf::Texture};
		if (newTexture->loadFromFile(mRootDir + path)) {
			mLoadedTextureMap.insert({path, newTexture});
			return newTexture;
		}
		return shared<sf::Texture>{nullptr};
	}

	void AssetManager::CleanCycle()
	{
		for (auto it = mLoadedTextureMap.begin(); it != mLoadedTextureMap.end();) {
			if (it->second.unique()) {
				LOG("Cleaning Texture %s ...", it->first.c_str());
				it = mLoadedTextureMap.erase(it);
			}
			else it++;
		}
	}

	void AssetManager::SetAssetRootDir(const std::string& dir)
	{
		mRootDir = dir;
	}

	AssetManager::AssetManager() {}
};
