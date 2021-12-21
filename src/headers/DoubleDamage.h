#pragma once
#include "Status.h"

class DoubleDamage : public Status {
public:
    DoubleDamage(int defaultTime_, double multiplication) : Status(defaultTime_) 
    {
        this->multiplication = multiplication;
    }

    void OnAcquire(Hero* hero) override;
    void OnRelease(Hero* hero) override;
private:
    double multiplication;
};