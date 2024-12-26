#pragma once 

#include "framework/Object.h"
#include "SFML/Graphics.hpp"
#include "framework/AssetManager.h"
#include "framework/MathUtil.h"
#include "framework/Core.h"

class b2Body;

namespace ly {
	class World;
	class Actor : public Object{
	private:
		World* mowningWorld;
		sf::Sprite mSprite; 
		shared<sf::Texture> mTexture;
		b2Body* mPhysicsBody;
		bool mEnablePhysics;
		uint8 mTeamID;
		const static uint8 neutralTeamID = 255;
		bool mHasBeganPlay;
		float mActorShootingAngle;
		//sf::Texture mTexture; // each Actor has a copy of a texture. use "flyweight pattern"

	public:
		Actor(World* owningWorld, const std::string& texturePath = "");
		virtual ~Actor();
		virtual void BeginPlay();
		virtual void Tick(float deltaTime);
		void BeginPlayInternal();
		void TickInternal(float deltaTime);
		void setTexture(const std::string& texturePath);
		void Render(sf::RenderWindow& window);
		sf::Sprite& GetSprite();
		const sf::Sprite& GetSprite() const;
		void SetActorShootingAngle(float fAngle);
		float GetActorShootingAngle() const { return mActorShootingAngle; }
		void CenterPivot();
		void SetActorLocation(const sf::Vector2f& newLocation);
		void SetActorRotation(float newRotation);
		void AddActorLocationOffset(const sf::Vector2f& offsetAmt);
		void AddActorRotationOffset(const float offsetAmt);
		sf::Vector2f GetActorLocation() const;
		float GetActorRotation() const;
		sf::Vector2f GetActorForwardDirection() const; 
		sf::Vector2f GetActorRightDirection() const;
		sf::FloatRect GetActorGlobalBounds() const;
		bool IsActorOutOfWindowBounds(float allowance = 10.0) const;
		sf::Vector2u GetWindowSize() const;
		World* GetWorld() const { return mowningWorld; }
		void InitializePhysics();
		void SetEnablePhysics(bool enable);
		void UnInitializePhysics();
		void UpdatePhysicsBodyTransform();
		virtual void OnActorBeginOverlap(Actor* actor);
		virtual void OnActorEndOverlap(Actor* actor);
		virtual void Destroy() override;
		static uint8 GetNeutralTeamID() { return neutralTeamID; }
		uint8 GetTeamID() const { return mTeamID; }
		bool isOtherHostile(Actor* other) const;
		void SetTeamID(uint8 teamID) { mTeamID = teamID; }
		virtual void ApplyDamage(float amt);
	};
}