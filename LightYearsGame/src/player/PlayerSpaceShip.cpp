#include "player/PlayerSpaceShip.h"
#include "SFML/System.hpp"
#include "weapon/BulletShooter.h"
#include "framework/Core.h"

ly::PlayerSpaceShip::PlayerSpaceShip(World* owningWorld, const std::string& path):
	SpaceShip(owningWorld, path), mMoveInput{}, mSpeed{ 200.f },mShooter{ new BulletShooter(this, 0.1f, {50.f, 0.f}) }
{
	SetTeamID(1);
	SetActorShootingAngle(-90.f);
}

void ly::PlayerSpaceShip::Tick(float DeltaTime)
{
	//LOG("Player Space Ship ticking ... ");
	SpaceShip::Tick(DeltaTime);
	HandleInput();
	ConsumeInput(DeltaTime);
}

void ly::PlayerSpaceShip::SetSpeed(float newSpeed) { mSpeed = newSpeed; }

void ly::PlayerSpaceShip::HandleInput() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		mMoveInput.y = -1.f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		mMoveInput.y = 1.f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		mMoveInput.x = -1.f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		mMoveInput.x = 1.f;
	}
	ClampInputOnEdge();
	NormalizeInput();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
		Shoot();
	}
}

void ly::PlayerSpaceShip::ConsumeInput(float DeltaTime) {
	setVelocity(mMoveInput * mSpeed);
	mMoveInput.x = mMoveInput.y = 0.f;
}

void ly::PlayerSpaceShip::NormalizeInput() {
	Normalize(mMoveInput);
	//LOG("Move input is now normalized ...%f %f", mMoveInput.x, mMoveInput.y);
}

void ly::PlayerSpaceShip::ClampInputOnEdge() {
	sf::Vector2f actorLocation = GetActorLocation();
	if (actorLocation.x < 0 && mMoveInput.x == -1) {
		mMoveInput.x = 0.f;
	}
	if (actorLocation.x > GetWindowSize().x && mMoveInput.x == 1) {
		mMoveInput.x = 0.f;
	}
	if (actorLocation.y < 0 && mMoveInput.y == -1) {
		mMoveInput.y = 0.f;
	}
	if (actorLocation.y > GetWindowSize().y && mMoveInput.y == 1) {
		mMoveInput.y = 0.f;
	}
}

void ly::PlayerSpaceShip::Shoot() {
	if (mShooter) {
		mShooter->Shoot();
	}
	/*LOG ("On Shoot:");
	mhealthComp.OnHealthChanged.BroadCast(10, 20, 30);*/
}