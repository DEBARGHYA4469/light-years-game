#include "Enemy/EnemySpaceShip.h"

ly::EnemySpaceShip::EnemySpaceShip(World* owningWorld, const std::string& texturePath, float mCollisionDamage):
	SpaceShip(owningWorld, texturePath), mCollisionDamage(mCollisionDamage)
{

}

void ly::EnemySpaceShip::Tick(float DeltaTime)
{
	SpaceShip::Tick(DeltaTime);
	if (IsActorOutOfWindowBounds(std::max(GetActorGlobalBounds().width, GetActorGlobalBounds().height))) {
		Destroy();
	} 
}

void ly::EnemySpaceShip::OnActorBeginOverlap(Actor* other)
{
	SpaceShip::OnActorBeginOverlap(other);
	if (isOtherHostile(other)) {
		other->ApplyDamage(mCollisionDamage);
	}
}
