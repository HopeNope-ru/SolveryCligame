#pragma once
#include "Defs.h"
#include "Boundary.h"
#include "Object.h"
#include "Coordinate.h"

class Camera {
public:
	Camera(Object* heroFollowing_, Object* frontier_);
	
	void drawColoredSpaceInCamCoords(const WCoord& coord, int color, char character);
	void move(const WorldCoordinate& delta);
public:
	Object* heroFollowing;
	Object* frontier;
	WorldCoordinate coordinate;
	Boundary boundary;
	Boundary lastBoundCam;
};