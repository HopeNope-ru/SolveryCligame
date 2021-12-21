#pragma once
#include "Defs.h"
#include "SingleCellObjectStatic.h"
#include "Coordinate.h"

class Status {
public:
	enum Kind {
		SPEEDUP,
		DD,
		STATUS_COUNT
	};

	Status(int defaultTime_) : defaultTime(defaultTime_)
	{ }

	virtual ~Status()
	{ }

	virtual void OnAcquire(Hero* hero) = 0;
	virtual void OnTimePassed(Hero* hero, int ticks) { };
	virtual void OnRelease(Hero* hero) = 0;
public:
	int defaultTime;
};