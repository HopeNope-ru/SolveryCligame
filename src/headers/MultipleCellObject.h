#pragma once
#include "Object.h"
#include "UtileFunctions.h"
#include "SingleCellObject.h"
#include "Coordinate.h"

class MultipleCellObject : public Object {
public:
	MultipleCellObject(int x_, int y_, Boundary bound, int color_, char character, GameState* gameState_);
	virtual ~MultipleCellObject() 
	{ }
	virtual void draw() override;
	virtual void onCollision(Object* other) override{ }
};