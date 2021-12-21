#pragma once
#include "Defs.h"
#include "Boundary.h"
#include "GridIndex.h"
#include "Camera.h"
#include "Coordinate.h"

class Object {
public:
	Object()
	{ }
	Object(int x_, int y_, int color_, 
        char character_, GameState* gameState_);
	Object(WCoord wCoord, GameState* game);

	virtual ~Object()
	{ }
	virtual void draw()=0;
	virtual void update() { }
	virtual bool destroy() { return false; }
	virtual void onCollision(Object* other) { }
public:
	int color;
	char character;
	Boundary boundary;
	WorldCoordinate coordinate;
	GameState* gameState;
};