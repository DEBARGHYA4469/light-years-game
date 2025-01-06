#pragma once 
#include "framework/Actor.h"
#include "gameplay/HealthComponent.h"

namespace ly {
	class SpaceShip : public Actor {
	public:
		SpaceShip(World* owningWorld, const std::string& texturePath = "");
		virtual void Tick(float deltaTime) override;
		void SetVelocity(sf::Vector2f newVelocity);
		sf::Vector2f getVelocity() const;
		virtual void Shoot();
		virtual void BeginPlay() override;
		virtual void ApplyDamage(float amt) override;
		void Blink();
		void UpdateBlink(float DeltaTime);
		HealthComponent& GetHealthComponent() { return mhealthComp; }
	private:
		sf::Vector2f mVelocity;
		float mBlinkTime;
		float mBlinkDuration;
		sf::Color mBlinkColorOffset;
	protected:
		HealthComponent mhealthComp;
		virtual void OnHealthChanged(float amt, float health, float maxHealth);
		virtual void OnTakenDamage(float amt, float health, float maxHealth);
		void Blow();
		virtual void Blew();
	};
}