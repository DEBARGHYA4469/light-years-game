#pragma once 
#include "framework/Delegate.h"

namespace ly {
	class HealthComponent {
	private:
		float mHealth;
		float mMaxHealth;
	public:
		HealthComponent(float health, float maxHealth);
		void ChangeHealth(float DeltaAmt);
		void SetInitialHealth(float health, float MaxHealth);
		float GetHealth() const { return mHealth; }
		float GetMaxHealth() const { return mMaxHealth; }
		
		//Event Listeners
		Delegate<float, float, float> OnHealthChanged;
		Delegate<float, float, float> OnTakenDamage;
		Delegate<> OnHealthEmpty;
	private:
		void TakenDamage(float Amt);
		void HealthEmpty();
		void HealthRegen(float Amt);
	};
};

// Requirement : A Delegate / Observer / Listener for the health fluctuations.