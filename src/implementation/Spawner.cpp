#include "Spawner.h"

Spawner::Spawner(WorldCoordinate coordinate_, uint64_t cdSpawn, GameState* gameState_)
	: SingleCellObject(coordinate_, cdSpawn, gameState_)
{ 
	coordinate = coordinate_;
	boundary.coordLeftUp.x = coordinate.x - 2;
	boundary.coordLeftUp.y = coordinate.y - 2;
	boundary.coordRightDown.x = coordinate.x + 2;
	boundary.coordRightDown.y = coordinate.y + 2;

	gameState = gameState_;
	gameState->turnQueue.push(this);
}

void Spawner::spawnMonster() {
	WorldCoordinate coord = random_range(boundary);
	Monsters* newM = new Monsters(coord.x, coord.y, 20.5, E_MONSTR, 20.0, ' ', 3, gameState);
	newM->nextTurn = gameState->gameTime;
}

void Spawner::update() {
	gameState->gameTime = nextTurn;
	nextTurn = gameState->gameTime + turnTime;
	
	spawnMonster();
}