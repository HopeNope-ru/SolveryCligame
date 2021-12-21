#include "GridIndex.h"

ListSCObject& GridIndex::GetObjectInPoint(WorldCoordinate coord) {
	index_x = coord.x / SIZE_CELL_XxY, index_y = coord.y / SIZE_CELL_XxY;
	return index[index_y][index_x];
}
