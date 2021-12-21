#pragma once
#include "SingleCellObject.h"
#include "Status.h"
#include "ApliedStatus.h"
#include "Item.h"
#include "DamageReceived.h"
#include "Coordinate.h"

class Hero : public SingleCellObject, public DamageReceived {
public:
	Hero(int x_, int y_, double damage, int color_, double health_,
		char character_, uint64_t cdMove, GameState* gameState_, std::map<Status::Kind, ApliedStatus>& status_);

	bool destroy() override;

	void onCollision(Object*) override;
	void move(const WorldCoordinate&)override;
	void takeDamage(double) override;
	void update() override;
	void PickUp();
	void PushItem(Status::Kind nameItem , Item* item);
	void UsePowerup(Status::Kind nameStatus);
protected:
	ListSCObject::iterator iterMngObj;
	std::map<Status::Kind, std::queue<Item*>> item;
	std::map<Status::Kind, ApliedStatus> status;
	friend class UI;
};