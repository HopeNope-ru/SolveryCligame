#include "Item.h"

void Item::draw() {
	if( !invisible )
		gameState->camera->drawColoredSpaceInCamCoords(coordinate, color, character);
}