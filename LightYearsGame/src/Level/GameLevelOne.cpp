#include <framework/TimerManager.h>
#include "framework/Actor.h"
#include <player/PlayerSpaceShip.h>
#include <Enemy/Vanguard.h>
#include "Level/GameLevelOne.h"
#include <Enemy/VanguardStage.h>
#include <Enemy/TwinBladeStage.h>
#include <gameplay/WaitStage.h>
#include <Enemy/HexagonStage.h>
#include <Enemy/Hexagon.h>
#include <Enemy/UFO.h>
#include <Enemy/UFOStage.h>
#include <player/PlayerManager.h>
#include <framework/Actor.h>
#include <player/Player.h>

ly::GameLevelOne::GameLevelOne(Application* app) :
	World(app)
{
	
}

void ly::GameLevelOne::BeginPlay() {
	Player newPlayer =  PlayerManager::Get().CreateNewPlayer();
	mPlayerSpaceShip = newPlayer.SpawnSpaceShip(this);
	mPlayerSpaceShip.lock()->onActorDestroyed.BindAction(GetWeakRef(), &GameLevelOne::PlayerSpaceShipDestroyed);
}

void ly::GameLevelOne::PlayerSpaceShipDestroyed(ly::Actor* destroyed) {
	mPlayerSpaceShip = PlayerManager::Get().GetPlayer()->SpawnSpaceShip(this);
	if (!mPlayerSpaceShip.expired()) { // Cannot Spawn Anymore
		mPlayerSpaceShip.lock()->onActorDestroyed.BindAction(GetWeakRef(), &GameLevelOne::PlayerSpaceShipDestroyed);
		return;
	}
	GameOver();
}

void  ly::GameLevelOne::GameOver() {
	LOG("Game Over ==============================================");
}

void ly::GameLevelOne::InitGameStages() {
	AddGameStage(shared<VanguardStage>(new VanguardStage(this)));
	AddGameStage(shared<TwinBladeStage>(new TwinBladeStage(this)));
	AddGameStage(shared<UFOStage>(new UFOStage(this)));
	AddGameStage(shared<HexagonStage>(new HexagonStage(this)));
}