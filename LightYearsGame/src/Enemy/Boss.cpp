#include "Enemy/Boss.h"
#include "gameplay/HealthComponent.h"

ly::Boss::Boss(World* world)
	: EnemySpaceShip(world, "SpaceShooterRedux/PNG/Enemies/boss.png"),
	mSpeed{100.f},
	mBaseSpeed{100.f},
	mSwitchDistanceToEdge{100.f},
	mBaseShooterLeft{ new BulletShooter(this, 1.f, {50.f, -50.f}) },
	mBaseShooterRight{ new BulletShooter(this, 1.f, {50.f, 50.f}) },
	mThreeWayShooter{ new ThreeWayShooter(this, 4.f, {100.f, 0.f}) },
	mFrontalWiperLeft{ new FrontalWiper(this, 5.f, {80.f, -100.f}) },
	mFrontalWiperRight{ new FrontalWiper(this, 5.f, {80.f, 100.f}) },
	mStage{1}
{
	SetActorRotation(90.f);
	SetTeamID(2);
	SetVelocity({ mSpeed, 0.f });
	SetRewardSpawnWeight(0);
	GetHealthComponent().SetInitialHealth(1000, 1000);
}

void ly::Boss::Tick(float Deltatime)
{	
	CheckMove();
	ShootBaseShooters();
	ShootThreeWayShooter();
	ShootFrontalWiper();
	EnemySpaceShip::Tick(Deltatime);
}

void ly::Boss::CheckMove()
{
	if (GetActorLocation().x > GetWindowSize().x - mSwitchDistanceToEdge) {
		SetVelocity({ -mSpeed, 0.f });
	}
	else if (GetActorLocation().x < mSwitchDistanceToEdge) {
		SetVelocity({ mSpeed, 0.f });
	}
}

void ly::Boss::BeginPlay()
{	
	EnemySpaceShip::BeginPlay();
	GetHealthComponent().OnHealthChanged.BindAction(GetWeakRef(), &Boss::HealthChanged);
}

void ly::Boss::ShootBaseShooters()
{
	mBaseShooterLeft->Shoot();
	mBaseShooterRight->Shoot();
}

void ly::Boss::ShootThreeWayShooter()
{
	mThreeWayShooter->Shoot();
}

void ly::Boss::ShootFrontalWiper()
{
	mFrontalWiperLeft->Shoot();
	mFrontalWiperRight->Shoot();
}

void ly::Boss::HealthChanged(float amt, float curr, float maxHealth)
{
	float percent = curr / maxHealth;
	if (percent < 0.7f && percent > 0.5f) {
		SetStage(2);
	}
	else if (percent < 0.5f) {
		SetStage(3);
	}
	else if (percent < 0.2f) {
		SetStage(4);
	}
} 

void ly::Boss::SetStage(int stage)
{
	mStage = stage;
	mBaseShooterLeft->SetCurrentLevel(stage);
	mBaseShooterRight->SetCurrentLevel(stage);
	mThreeWayShooter->SetCurrentLevel(stage);
	mFrontalWiperLeft->SetCurrentLevel(stage);
	mFrontalWiperRight->SetCurrentLevel(stage);
	mSpeed = mStage * mBaseSpeed;
}

void ly::Boss::IncreaseStage()
{
	mStage += 1;
}
