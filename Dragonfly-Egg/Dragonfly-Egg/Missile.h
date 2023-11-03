#pragma once
#ifndef __MISSILE_H__
#define __MISSILE_H__
#include "Projectile.h"
class Missile : public Projectile {
private:


public:
	Missile(df::Vector direction, df::Vector position, int player_owner);
};
#endif