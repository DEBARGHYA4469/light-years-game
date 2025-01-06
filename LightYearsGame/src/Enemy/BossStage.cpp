#include "Enemy/BossStage.h"
#include "Enemy/Boss.h"
#include "framework/World.h"

ly::BossStage::BossStage(World* world): GameStage(world)
{
}

void ly::BossStage::StartStage()
{
	auto windowSize = GetWorld()->GetWindowSize();
	weak<Boss> boss = GetWorld()->SpawnActor<Boss>();
	boss.lock()->SetActorLocation(sf::Vector2f{ windowSize.x / 2.f, 200.f });
	boss.lock()->onActorDestroyed.BindAction(GetWeakRef(), &BossStage::BossDestroyed);
}

void ly::BossStage::BossDestroyed(Actor* actor)
{
	FinishStage();
}
