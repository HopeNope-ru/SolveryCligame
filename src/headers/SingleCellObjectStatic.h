#pragma once
#include "Object.h"

class SingleCellObjectStatic : public Object {
public:
    SingleCellObjectStatic(WCoord coordinate_, int color, char character, GameState* gameState);
    
    virtual void draw() override;
};