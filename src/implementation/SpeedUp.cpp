#include "SpeedUp.h"
#include "Hero.h"

void SpeedUp::OnAcquire(Hero* hero) {
	hero->turnTime /= boost;
}

void SpeedUp::OnRelease(Hero* hero) {
	hero->turnTime *= boost;
}