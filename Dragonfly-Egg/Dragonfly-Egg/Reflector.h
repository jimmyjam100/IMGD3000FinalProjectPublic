#pragma once
#include "Attack.h"
#include "Projectile.h"
class Reflector : public Projectile {
private:
	int active_time;
	bool has_hit;

public:
	Reflector(df::Vector position, int player_owner);
	int getActiveTime() const;
	void setActiveTime(int new_active_time);
	bool hasHit() const;
	void setHasHit(bool new_bool);
	bool isEarly() const;
	int eventHandler(const df::Event* p_e);
	~Reflector();
};