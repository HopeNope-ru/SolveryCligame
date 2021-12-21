#include "MultipleCellObject.h"

MultipleCellObject::MultipleCellObject(int x_, int y_,
	Boundary bound,	int color_, char character_, GameState* gameState_)
	: Object(x_, y_, color_, character_, gameState_)
{
	boundary = bound;
	gameState->MCObjects->push_back(this);
}

void MultipleCellObject::draw() {
	for(int y_i = boundary.coordLeftUp.y; y_i <= boundary.coordRightDown.y; y_i++)
			for(int x_j = boundary.coordLeftUp.x; x_j <= boundary.coordRightDown.x; x_j++)
				gameState->camera->drawColoredSpaceInCamCoords(WCoord{x_j, y_i}, color, character);
}