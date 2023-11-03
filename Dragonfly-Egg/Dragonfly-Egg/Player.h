#pragma once
#ifndef __PLAYER_H__
#define __PLAYER_H__
#include "Object.h"
#include "Event.h"
#include "EventGamepad.h"
#include "Projectile.h"
#include "ViewObject.h"
#include "ChargeShot.h"
#include "Reflector.h"
#include "Logo.h"

class Player : public df::Object {
private:
	bool m_right;
	int m_cooldown;
	int m_hitstun;
	int m_playernum;
	int m_percent;
	Player* p_other_player;
	float m_player_speed;
	df::ViewObject* vo;
	df::ViewObject* stock_vo;
	bool is_charging;
	ChargeShot* m_charge_shot;
	Reflector* m_reflector;
	Reflector* old_reflector;
	bool holdJump;
	bool usedDouble;
	bool jumping;
	int stocks;
	bool alreadyOut;
	int m_taunt_cooldown;
	int m_shoot_cooldown;
	std::string current_sprite;
	df::Object* m_logo;

public:
	Player(bool right, df::Object *logo);
	~Player();
	int eventHandler(const df::Event* p_e);
	void hanndleGamepad(df::EventGamepad *e);
	void hanndleStep();
	void hanndleKnockback(Attack *p);
	void shoot(int weapon);
	int getPlayerNum() const;
	bool hasReflecter() const;
	void setCooldown(int cooldown);
	ChargeShot* getChargeShot() const;
	void setChargeShot(ChargeShot* c);
	Reflector* getReflector() const;
	void setReflector(Reflector* r);
	void setIsCharging(bool c);
	void endGame();

};
#endif