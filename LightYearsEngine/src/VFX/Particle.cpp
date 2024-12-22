#include "VFX/Particle.h"
#include "framework/MathUtil.h"

ly::Particle::Particle(World* owningWorld, const std::string texturePath):
	Actor(owningWorld, texturePath), mTimer{}, mVelocity{}, mLifeTime{1.f}
{
}

void ly::Particle::Tick(float DeltaTime)
{
	Actor::Tick(DeltaTime);
	Move(DeltaTime);
	Fade(DeltaTime);

	if (mTimer.getElapsedTime().asSeconds() > mLifeTime) {
		Destroy();
	}
}

void ly::Particle::RandomVelocity(float minSpeed, float maxSpeed)
{
	mVelocity = RandomUnitVector() * RandomRange(minSpeed, maxSpeed);
}

void ly::Particle::RandomSize(float min, float max)
{
	float randScale = RandomRange(min, max);
	GetSprite().setScale(randScale, randScale);
}

void ly::Particle::RandomLifeTime(float min, float max)
{
	mLifeTime = RandomRange(min, max);
}

void ly::Particle::Move(float DeltaTime)
{
	AddActorLocationOffset(mVelocity * DeltaTime);
}

void ly::Particle::Fade(float DeltaTime)
{
	float elapsedTime = mTimer.getElapsedTime().asSeconds();
	float alpha = elapsedTime / mLifeTime;
	GetSprite().setColor(LerpColor(GetSprite().getColor(), sf::Color(255,255,255,0), alpha)); // become transparent
	GetSprite().setScale(LerpVector(GetSprite().getScale(), sf::Vector2f(0,0), alpha)); // become smaller
}
