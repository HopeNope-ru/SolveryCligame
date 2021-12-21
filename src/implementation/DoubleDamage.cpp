#include "DoubleDamage.h"
#include "Hero.h"

void DoubleDamage::OnAcquire(Hero* hero) {
    hero->damage *= multiplication;
}

void DoubleDamage::OnRelease(Hero* hero) {
    hero->damage /= multiplication;
}