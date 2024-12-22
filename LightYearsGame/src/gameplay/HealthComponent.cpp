#include "gameplay/HealthComponent.h"
#include "framework/Core.h"

ly::HealthComponent::HealthComponent(float health, float maxHealth)
{
	mHealth = health;
	mMaxHealth = maxHealth;
}

void ly::HealthComponent::ChangeHealth(float DeltaAmt)
{	
	if (mHealth == 0) return;
	if (DeltaAmt == 0) return;
	mHealth += DeltaAmt;

	if (mHealth < 0) mHealth = 0;
	if (mHealth > mMaxHealth) mHealth = mMaxHealth;
	
	if (DeltaAmt < 0) { 
		TakenDamage(-DeltaAmt);
		if (mHealth <= 0) {
			HealthEmpty();
		}
	}
	else {
		HealthRegen(DeltaAmt);
	}
	OnHealthChanged.BroadCast(DeltaAmt, mHealth, mMaxHealth);
}
void ly::HealthComponent::TakenDamage(float Amt)
{
	OnTakenDamage.BroadCast(Amt, mHealth, mMaxHealth);
	LOG("Took Damage: %f now health is: %f/%f", Amt, mHealth, mMaxHealth);
}

void ly::HealthComponent::HealthEmpty()
{
	LOG("Dead");
	OnHealthEmpty.BroadCast();
}

void ly::HealthComponent::HealthRegen(float Amt)
{
	LOG("Health Regenerated: %f now health is: %f/%f", Amt, mHealth, mMaxHealth);
}

