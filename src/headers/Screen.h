#pragma once
#include "Defs.h"
#include "Boundary.h"
#include "Coordinate.h"

class Screen {
public:
	Screen(Boundary sizeScreenBoundary);
	bool outFrontierScreen(LocalCoordinate& prevCamera);
public:
	Boundary viewBound;
	Boundary sizeBound;
};