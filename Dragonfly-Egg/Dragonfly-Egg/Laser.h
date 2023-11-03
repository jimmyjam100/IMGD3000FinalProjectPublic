#pragma once
#ifndef __LASER_H__
#define __LASER_H__
#include "Projectile.h"
class Laser : public Projectile {
private:


public:
	Laser(df::Vector direction, df::Vector position, int player_owner);
};
#endif