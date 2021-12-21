#pragma once
#include "Defs.h"
#include "Boundary.h"
#include "SingleCellObject.h"
#include "MultipleCellObject.h"
#include "Coordinate.h"

void drawColoredSpace(int x, int y, int color, char character);
void clearStr(int xMin, int xMax, int y);
WorldCoordinate random_range(Boundary&);
Boundary mirrorBoundaryCoordinate(const Boundary& mrrBoundary);

bool pressedDirection(int dir);
bool intersects(Object* b1, Object* b2);
bool intersects(const WCoord& wCoord, Object* b2);