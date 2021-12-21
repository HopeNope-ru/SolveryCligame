#include "Column.h"

Column::Column(int x_, int y_, Boundary bound, int color_, char character_, GameState* gameState_)
    : MultipleCellObject(x_, y_, bound, color_, character_, gameState_)
{ }

void Column::update() {
	draw();
}