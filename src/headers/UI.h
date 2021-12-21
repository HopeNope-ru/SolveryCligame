#pragma once
#include "Hero.h"
#include "Coordinate.h"

class UI : public Object {
private:
	Hero* hero;
public:
	UI(Hero*);
	
	virtual void draw() override;
	virtual void update();
};