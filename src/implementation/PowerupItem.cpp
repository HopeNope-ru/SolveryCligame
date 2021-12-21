#include "PowerupItem.h"
#include "Hero.h"

PowerupItem::PowerupItem(Status::Kind nameItem_, WCoord coordinate_, int color_, char character_, 
	GameState* gameState_, Status* status_)
	: Item(nameItem_, coordinate_, color_, character_, gameState_), status(status_)
{ }

void PowerupItem::OnPickup() {
	if( !pickedUp ) {
		gameState->hero->PushItem(nameItem, this);
		pickedUp = true;
		invisible = true;
	}
}