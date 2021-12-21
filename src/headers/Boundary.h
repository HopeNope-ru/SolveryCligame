#pragma once
#include "Defs.h"
#include "Coordinate.h"

//////////////////////////////////////////////////
// класс задающий границы объектам
class Boundary {
public:
	WorldCoordinate coordLeftUp;
	WorldCoordinate coordRightDown;

	void mirrorCoordinate(WCoord&, WCoord&) const;
};