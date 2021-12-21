#pragma once
#include "Defs.h"
#include "MultipleCellObject.h"
#include "Coordinate.h"

class Column : public MultipleCellObject {
public:
	Column(int x_, int y_, Boundary bound, int color_, char character_, GameState* gameState_);

	void update() override;
};