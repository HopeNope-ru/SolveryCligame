#pragma once
#include "Defs.h"
#include "SingleCellObject.h"
#include "Hero.h"
#include "DamageReceived.h"
#include "Coordinate.h"
#include "Astar.h"

class Monsters : public SingleCellObject, public DamageReceived {
public:
	Monsters(int x_, int y_, double damage, int color_, double health_, char character, uint64_t cdMove, GameState* gameState_);
	
	void onCollision(Object*) override;
	void takeDamage(double) override;
	void update() override;
	bool destroy() override;
protected:
	ListSCObject::iterator iterMngObj;
};