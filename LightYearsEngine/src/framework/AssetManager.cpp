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
		return LoadAsset(path, mLoadedTextureMap);
	}

	shared<sf::Font> AssetManager::LoadFont(const std::string& path)
	{
		return LoadAsset(path, mLoadedFontMap);
	}

	void AssetManager::CleanCycle()
	{
		CleanUniqueRef(mLoadedFontMap);
		CleanUniqueRef(mLoadedTextureMap);
	}

	void AssetManager::SetAssetRootDir(const std::string& dir)
	{
		mRootDir = dir;
	}

	AssetManager::AssetManager() {}
};
