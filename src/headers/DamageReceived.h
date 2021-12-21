#pragma once

class DamageReceived {
public:
	DamageReceived(double health_);
	virtual ~DamageReceived()
	{ }
	virtual void takeDamage(double damage) = 0;
public:
	bool death = false;
protected:
	double health;
};
