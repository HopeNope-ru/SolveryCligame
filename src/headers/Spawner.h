#pragma once
#include "Object.h"
#include "Monsters.h"
#include "Coordinate.h"

class Spawner : public SingleCellObject {
public:
	Spawner(WorldCoordinate coordinate_, uint64_t cdSpawn, GameState* gameState_);

	void draw() override { }
	void update() override;
	void spawnMonster();
};