#pragma once
#include "Defs.h"
#include "Status.h"

class ApliedStatus {
public:
    ApliedStatus(Status* status_, GameState* gameState_);
    void Apply(Hero* hero);
    bool IsAplied() { return enabled; }
    void Update();
protected:
    Status* status;
    bool enabled;
    GameState* gameState;
    uint64_t timeRemaining;
};