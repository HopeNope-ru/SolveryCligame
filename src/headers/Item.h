#pragma once
#include "Defs.h"
#include "SingleCellObjectStatic.h"
#include "Coordinate.h"
#include "Status.h"

class Item : public SingleCellObjectStatic {
public:
    Item(Status::Kind nameItem_, WCoord coordinate_, int color_, char character_, GameState* gameState_) 
	: SingleCellObjectStatic(coordinate_, color_, character_, gameState_), nameItem(nameItem_)
	{ 
        pickedUp = false;
		invisible = false;
    }

	virtual ~Item()
	{ }

	virtual void OnPickup() = 0;
	virtual void draw() override;
protected:
	Status::Kind nameItem;
	bool invisible;
    bool pickedUp;
};