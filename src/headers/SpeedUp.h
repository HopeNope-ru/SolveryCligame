#pragma once
#include "Status.h"

class SpeedUp : public Status {
public:
	SpeedUp(int defaultTime, int boost_) : Status(defaultTime), boost(boost_) 
	{ }

	void OnAcquire(Hero* hero) override;
	void OnRelease(Hero* hero) override;
private:
	uint64_t boost;
};