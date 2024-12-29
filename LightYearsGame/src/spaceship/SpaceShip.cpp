#include "spaceship/SpaceShip.h"
#include "framework/MathUtil.h"
#include "VFX/Explosion.h"


ly::SpaceShip::SpaceShip(World* owningWorld, const std::string& texturePath) :
	Actor(owningWorld, texturePath), mVelocity{}, mhealthComp(100, 100), mBlinkTime(0.f), mBlinkDuration(0.2f), mBlinkColorOffset({255, 0, 0, 255})
{
}

void ly::SpaceShip::Tick(float deltaTime)
{
	//LOG("Space Ship Tick ...");
	Actor::Tick(deltaTime);
	AddActorLocationOffset(getVelocity() * deltaTime);
	UpdateBlink(deltaTime);
}

void ly::SpaceShip::setVelocity(sf::Vector2f newVelocity)
{
	mVelocity = newVelocity;
}

sf::Vector2f ly::SpaceShip::getVelocity() const
{
	return mVelocity;
}

void ly::SpaceShip::Shoot()
{
}

void ly::SpaceShip::BeginPlay()
{
	Actor::BeginPlay();
	SetEnablePhysics(true);

	// subscribe to all the events from health change
	// Observer Design Pattern, Event Listener

	mhealthComp.OnHealthChanged.BindAction(GetWeakRef(), &SpaceShip::OnHealthChanged);
	mhealthComp.OnTakenDamage.BindAction(GetWeakRef(), &SpaceShip::OnTakenDamage);
	mhealthComp.OnHealthEmpty.BindAction(GetWeakRef(), &SpaceShip::Blow);
}

void ly::SpaceShip::ApplyDamage(float amt)
{	
	mhealthComp.ChangeHealth(-amt);
	LOG("Damage of %f, suffered", amt);
}

void ly::SpaceShip::Blink()
{
	if (mBlinkTime == 0) { mBlinkTime = mBlinkDuration; }
}

void ly::SpaceShip::UpdateBlink(float DeltaTime)
{
	if (mBlinkTime > 0) {
		mBlinkTime -= DeltaTime;
		mBlinkTime = mBlinkTime > 0 ? mBlinkTime : 0;
		// sprite multiplier on top of texture. 
		GetSprite().setColor(LerpColor(sf::Color::White, mBlinkColorOffset, mBlinkTime));
	}
}

void ly::SpaceShip::OnHealthChanged(float amt, float health, float maxHealth)
{
	LOG("Health changed by %f, and is now: %f / %f", amt, health, maxHealth);
}

void ly::SpaceShip::OnTakenDamage(float amt, float health, float maxHealth)
{
	Blink();
}

void ly::SpaceShip::Blow()
{
	Explosion* explosion = new Explosion();
	explosion->SpawnExplosion(GetWorld(), GetActorLocation());
	Blew();
	Destroy();
	delete explosion;
}

void ly::SpaceShip::Blew()
{
}
