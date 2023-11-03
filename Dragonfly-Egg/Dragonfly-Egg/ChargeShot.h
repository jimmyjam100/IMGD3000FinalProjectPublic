#pragma once
#ifndef __CHARGESHOT_H__
#define __CHARGESHOT_H__
#include "Projectile.h"
class ChargeShot : public Projectile {
private:
	int m_charge;
	int small_dmg;
	df::Vector small_kb;
	int small_hs;
	int medium_dmg;
	df::Vector medium_kb;
	int medium_hs;
	int large_dmg;
	df::Vector large_kb;
	int large_hs;
	int small_to_medium;
	int medium_to_large;
	int full;
	bool can_hit;
	std::string size;

public:
	ChargeShot(df::Vector direction, df::Vector position, int player_owner);
	void setCharge(int new_charge);
	int getCharge() const;
	bool isFullyCharged() const;
	bool canHit() const;
	void setCanHit(bool new_bool);
	void shootFull();
	void updateSprite();
	std::string getSize() const;
	~ChargeShot();
};
#endif