#include "player/PlayerSpaceShip.h"
#include "SFML/System.hpp"
#include "weapon/BulletShooter.h"
#include "framework/Core.h"
#include "weapon/ThreeWayShooter.h"
#include "weapon/FrontalWiper.h"
#include "framework/TimerManager.h"

ly::PlayerSpaceShip::PlayerSpaceShip(World* owningWorld, const std::string& path):
	SpaceShip(owningWorld, path), 
	mMoveInput{}, 
	mSpeed{ 200.f },
	mShooter{ new FrontalWiper(this) },
	mInvulnerableTime{ 2.f }, 
	mInvulerableFlashInterval{ 0.5f }, 
	mInvulnerableFlashTimer{0.f},
	mInvulnerableFlashDirection{1}
{
	SetTeamID(1);
	mInVulnerable = true;
}

void ly::PlayerSpaceShip::Tick(float DeltaTime)
{
	//LOG("Player Space Ship ticking ... ");
	SpaceShip::Tick(DeltaTime);
	HandleInput();
	ConsumeInput(DeltaTime);
	UpdateInvulnerable(DeltaTime);
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
	SetVelocity(mMoveInput * mSpeed);
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
}

void ly::PlayerSpaceShip::SetShooter(unique<Shooter>&& shooter)
{
	if (mShooter && typeid(*mShooter.get()) == typeid(*shooter.get())) { // RTTI
		mShooter->IncrementLevel();
		return;
	}
	mShooter = std::move(shooter);
}

void ly::PlayerSpaceShip::ApplyDamage(float amt)
{
	if (!mInVulnerable) {
		SpaceShip::ApplyDamage(amt);
	}
}

void ly::PlayerSpaceShip::BeginPlay()
{
	TimerManager::Get().SetTimer(GetWeakRef(), &PlayerSpaceShip::StopInvulnerable , mInvulnerableTime);
	SpaceShip::BeginPlay();
}

void ly::PlayerSpaceShip::StopInvulnerable()
{	
	GetSprite().setColor({255,255,255,255});
	mInVulnerable = false;
}

void ly::PlayerSpaceShip::UpdateInvulnerable(float DeltaTime)
{
	if (!mInVulnerable) return;
	mInvulnerableFlashTimer += DeltaTime * mInvulnerableFlashDirection;
	if (mInvulnerableFlashTimer < 0 || mInvulnerableFlashTimer > mInvulerableFlashInterval) {
		mInvulnerableFlashDirection *= -1;
	}
	GetSprite().setColor(LerpColor({255,255,255,64}, {255,255,255,128}, mInvulnerableFlashTimer / mInvulerableFlashInterval));
}
