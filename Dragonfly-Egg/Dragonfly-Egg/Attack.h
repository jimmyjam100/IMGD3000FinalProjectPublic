#pragma once
#ifndef __ATTACK_H__
#define __ATTACK_H__
#include "Object.h"
#include "EventCollision.h"

class Attack : public df::Object {
private:
	df::Vector m_knockback;
	int m_hitstun;
	int m_damage;
	int m_player_owner;


public:
	Attack();
	int eventHandler(const df::Event* p_e);
	void hit(const df::EventCollision* p_collision_event);
	df::Vector getKnockback() const;
	void setKnockback(df::Vector new_knockback);
	int getHitstun() const;
	void setHitstun(int new_hitstun);
	int getDamage() const;
	void setDamage(int new_damage);
	int getPlayerOwner() const;
	void setPlayerOwner(int new_player_owner);
};

#endif