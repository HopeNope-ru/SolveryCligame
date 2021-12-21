#pragma once
#include "MultipleCellObject.h"
#include "Coordinate.h"

class Wall : public MultipleCellObject {
public:
	Wall(Boundary bound, int color_, char character_, GameState* gameState_);
	void draw() override;
	void update() override;
};