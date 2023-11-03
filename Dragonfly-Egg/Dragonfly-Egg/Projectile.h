#pragma once
#ifndef __PROJECTILE_H__
#define __PROJECTILE_H__
#include "Attack.h"
#include "EventCollision.h"

class Projectile : public Attack {
private:
	void hit(const df::EventCollision* p_collision_event);

public:
	Projectile();
	int eventHandler(const df::Event* p_e);
};

#endif