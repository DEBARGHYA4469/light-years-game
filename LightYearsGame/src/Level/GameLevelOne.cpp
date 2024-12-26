#include <framework/TimerManager.h>
#include "framework/Actor.h"
#include <player/PlayerSpaceShip.h>
#include <Enemy/Vanguard.h>
#include "Level/GameLevelOne.h"
#include <Enemy/VanguardStage.h>

ly::GameLevelOne::GameLevelOne(Application* app) :
	World(app)
{
	testplayerSpaceShip = SpawnActor<PlayerSpaceShip>();
	testplayerSpaceShip.lock()->setTexture("SpaceShooterRedux/PNG/playerShip1_blue.png");
	testplayerSpaceShip.lock()->SetActorLocation(sf::Vector2f(400, 400));
	testplayerSpaceShip.lock()->SetActorRotation(0.f);
}

void ly::GameLevelOne::BeginPlay() {

}


void ly::GameLevelOne::InitGameStages() {
	AddGameStage(shared<VanguardStage> (new VanguardStage(this)));
}