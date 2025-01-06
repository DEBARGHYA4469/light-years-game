#pragma once 
#include "framework/Core.h"
#include "SFML/Graphics.hpp"

namespace ly {
	class AssetManager { // use SingleTon pattern
	public:
		static AssetManager& Get();
		shared<sf::Texture> LoadTexture (const std::string& path);
		shared<sf::Font> LoadFont(const std::string& path);

		template <typename T> 
		inline shared<T> LoadAsset(const std::string& path, Dictionary<std::string, shared<T>>& container) {
			auto found = container.find(path);
			if (found != container.end()) return found->second;
			shared<T> newAsset(new T);
			if (newAsset->loadFromFile(mRootDir + path)) {
				container.insert({ path, newAsset });
				return newAsset;
			}
			return shared<T>(nullptr);
		}

		template <typename T>
		inline void CleanUniqueRef(Dictionary <std::string, shared<T>>& assetMap) {
			for (auto it = assetMap.begin(); it != assetMap.end();) {
				if (it->second.unique()) {
					LOG("Cleaning Asset %s ...", it->first.c_str());
					it = assetMap.erase(it);
				}
				else it++;
			}
		}
		
		void CleanCycle();
		void SetAssetRootDir(const std::string& dir);
	protected:
		AssetManager();
	private:
		std::string mRootDir;
		static unique<AssetManager> assetManager;
		Dictionary<std::string, shared<sf::Texture>> mLoadedTextureMap;
		Dictionary<std::string, shared<sf::Font>> mLoadedFontMap;
	};
};