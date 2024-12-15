#pragma once 

#include "framework/Object.h"
#include "SFML/Graphics.hpp"
#include "framework/AssetManager.h"
#include "framework/MathUtil.h"

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
		Actor(World * owningWorld, const std::string & texturePath);
		Actor(World* owningWorld);
		virtual ~Actor();
		void BeginPlayInternal();
		void TickInternal(float deltaTime);
		void CenterPivot();
		void setTexture(const std::string& texturePath);
		void Render(sf::RenderWindow& window);
		void setActorLocation(const sf::Vector2f& newLocation);
		void setActorRotation(float newRotation);
		void AddActorLocationOffset(const sf::Vector2f& offsetAmt);
		void AddActorRotationOffset(const float offsetAmt);
		sf::Vector2f GetActorLocation() const;
		float GetActorRotation() const;
		sf::Vector2f GetActorForwardDirection() const; 
		sf::Vector2f GetActorRightDirection() const;
		sf::Vector2u GetWindowSize() const;

		virtual void BeginPlay();
		virtual void Tick(float deltaTime);
	};
}