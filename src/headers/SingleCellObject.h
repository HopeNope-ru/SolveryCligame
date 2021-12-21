#pragma once
#include "Object.h"
#include "UtileFunctions.h"
#include "MultipleCellObject.h"
#include "Coordinate.h"


class SingleCellObject : public Object {
public:
	SingleCellObject(int x_, int y_, double damage, int color_, char character_, 
					uint64_t cooldown, GameState* gameState_);
					
	SingleCellObject(WCoord wCoord, uint64_t cooldown, GameState* game);

	virtual ~SingleCellObject() 
	{ }
	virtual void draw() override;
	virtual void update() override { }
	virtual void onCollision(Object*) override { }
	virtual void move(const WorldCoordinate&);
public:
	double damage;
	uint64_t turnTime;
  	uint64_t nextTurn = 0ULL;
protected:
	ListSCObject::iterator iterGrid;
};