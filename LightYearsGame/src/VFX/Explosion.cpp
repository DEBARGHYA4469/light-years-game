#include "VFX/Explosion.h"
#include "VFX/Particle.h"
#include "framework/World.h"
#include "framework/MathUtil.h"

ly::Explosion::Explosion(int mParticleAmt, float mDuration, float mLifeTimeMin, float mLifeTimeMax, float mSizeMin, float mSizeMax, float mSpeedMin, float mSpeedMax, const List<std::string> mParticleImgPath, const sf::Color& mParticleColor)
	: mParticleAmt(mParticleAmt),
	mDuration(mDuration),
	mLifeTimeMin(mLifeTimeMin),
	mLifeTimeMax(mLifeTimeMax),
	mSizeMin(mSizeMin),
	mSizeMax(mSizeMax),
	mSpeedMin(mSpeedMin),
	mSpeedMax(mSpeedMax),
	mParticleImgPath(mParticleImgPath),
	mParticleColor(mParticleColor)
{
	
}

void ly::Explosion::SpawnExplosion(World* world, const sf::Vector2f& actorLocation)
{
	if (!world) return;
	for (int i = 0; i < mParticleAmt; i++) {
		std::string particleImgPath = mParticleImgPath[ (int) RandomRange(0, mParticleImgPath.size())];
		weak<Particle> newParticle = world->SpawnActor<Particle>(particleImgPath);
		newParticle.lock()->RandomSize(mSizeMin, mSizeMax);
		newParticle.lock()->RandomVelocity(mSpeedMin, mSpeedMax);
		newParticle.lock()->SetActorLocation(actorLocation);
		newParticle.lock()->RandomLifeTime(mLifeTimeMin, mLifeTimeMax);
		newParticle.lock()->GetSprite().setColor(mParticleColor);
	}
}
