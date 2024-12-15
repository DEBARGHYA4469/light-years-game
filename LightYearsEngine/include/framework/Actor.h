#pragma once 

#include "framework/Object.h"
#include "SFML/Graphics.hpp"
#include "framework/AssetManager.h"

namespace ly {
	class World;
	class Actor : public Object{
	private:
		World* mowningWorld;
		bool mHasBeganPlay;
		sf::Sprite mSprite; 
		//sf::Texture mTexture; // each Actor has a copy of a texture. use "flyweight pattern"
		shared<sf::Texture> mTexture;
	public:
		Actor(World* owningWorld, const std::string& texturePath);
		Actor(World* owningWorld);
		virtual ~Actor();
		void BeginPlayInternal();
		void TickInternal(float deltaTime);
		void setTexture(const std::string& texturePath);
		void Render(sf::RenderWindow& window);
		virtual void BeginPlay();
		virtual void Tick(float deltaTime);
	};
}