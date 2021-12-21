#pragma once
#include "Defs.h"
#include "Coordinate.h"

class GridIndex {
public:
	int index_x, index_y; // Для проверки местоположения героя, потом уберу их в функцию
	ListSCObject& GetObjectInPoint(WorldCoordinate coord);
private:
	ListSCObject index[WINDOW_Y / SIZE_CELL_XxY][WINDOW_X / SIZE_CELL_XxY]; 
};