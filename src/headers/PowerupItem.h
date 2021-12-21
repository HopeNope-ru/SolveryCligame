#pragma once
#include "Status.h"
#include "Item.h"
#include "Coordinate.h"

class PowerupItem : public Item {
public:
	PowerupItem(Status::Kind nameItem_, WCoord coordinate_, 
		int color_, char character_, GameState* gameState_, Status* status_); 

	void OnPickup() override;
public:
    Status* status;
};
