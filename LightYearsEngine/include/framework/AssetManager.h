#pragma once 
#include "framework/Core.h"
#include "SFML/Graphics.hpp"

namespace ly {
	class AssetManager { // use SingleTon pattern
	public:
		static AssetManager& Get();
		shared<sf::Texture> LoadTexture(const std::string& path);
		void CleanCycle();
	protected:
		AssetManager();
	private:
		static unique<AssetManager> assetManager;
		Dictionary<std::string, shared<sf::Texture>> mLoadedTextureMap;
	};
};