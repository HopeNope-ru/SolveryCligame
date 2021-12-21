#include "SingleCellObjectStatic.h"

SingleCellObjectStatic::SingleCellObjectStatic(WCoord coordinate_, int color_,
    char character_, GameState* gameState_)
    : Object(coordinate_.x, coordinate_.y, color_, character_, gameState_)
{ }

void SingleCellObjectStatic::draw() {
    gameState->camera->drawColoredSpaceInCamCoords(coordinate, color, character);
}