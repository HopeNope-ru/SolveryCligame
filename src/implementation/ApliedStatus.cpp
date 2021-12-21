#include "ApliedStatus.h"
#include "Hero.h"

ApliedStatus::ApliedStatus(Status* status_, GameState* gameState_)
{
    status = status_;
    gameState = gameState_;
    enabled = false;
}

void ApliedStatus::Apply(Hero* hero) {
    if( !enabled ) {
        status->OnAcquire(hero);
        timeRemaining = gameState->gameTime + status->defaultTime;
        enabled = true;
    }
}

void ApliedStatus::Update() {
    Hero* h = gameState->hero;
    if(timeRemaining <= gameState->gameTime)
        status->OnRelease(h);
}