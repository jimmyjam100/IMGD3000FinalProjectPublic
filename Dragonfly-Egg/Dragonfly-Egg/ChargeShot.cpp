#include "ChargeShot.h"
#include "WorldManager.h"
#include "Player.h"

ChargeShot::ChargeShot(df::Vector direction, df::Vector position, int player_owner) {
	// initialize differing values for size
	small_dmg = 5;
	small_kb = df::Vector(1, -1);
	small_hs = 10;
	medium_dmg = 12;
	medium_kb = df::Vector(0, -2);
	medium_hs = 60;
	large_dmg = 30;
	large_kb = df::Vector(3, -4);
	large_hs = 50;
	small_to_medium = 35;
	medium_to_large = 70;
	full = 90;
	m_charge = 0;
	can_hit = false;
	size = "small";
	// 
	setDamage(small_dmg);
	setKnockback(small_kb);
	setHitstun(small_hs);
	setSprite("scs");
	setDirection(direction);
	setSpeed(0);
	setPosition(position);
	setType("ChargeShot");
	setSolidness(df::SOFT);
	setPlayerOwner(player_owner);
}

void ChargeShot::setCharge(int new_charge) {
	m_charge = new_charge;
	if (new_charge == small_to_medium) {
		setDamage(medium_dmg);
		setHitstun(medium_hs);
		setKnockback(medium_kb);
		setSprite("mcs");
		size = "medium";
	} else if (new_charge == medium_to_large) {
		setDamage(large_dmg);
		setHitstun(large_hs);
		setKnockback(large_kb);
		setSprite("lcs");
		size = "large";
	}
	else if (new_charge == full) {
		setDamage(large_dmg * 1.1);
		setHitstun(large_hs * 1.1);
		df::Vector full_kb = large_kb;
		full_kb.scale(1.1);
		setKnockback(full_kb);
		size = "large";
	}
}

int ChargeShot::getCharge() const {
	return m_charge;
}

bool ChargeShot::isFullyCharged() const
{
	if (m_charge >= full) {
		return true;
	}
	return false;
}

bool ChargeShot::canHit() const {
	return can_hit;
}

void ChargeShot::setCanHit(bool new_bool)
{
	can_hit = new_bool;
}

void ChargeShot::shootFull()
{
	setSpeed(.75);
	setSprite("lcs");
	can_hit = true;
}

void ChargeShot::updateSprite()
{
	if (m_charge < small_to_medium) {
		setSprite("scs");
	}
	else if (m_charge >= small_to_medium && m_charge < medium_to_large) {
		setSprite("mcs");
	}
	else {
		setSprite("lcs");
	}
}

std::string ChargeShot::getSize() const
{
	return size;
}

ChargeShot::~ChargeShot()
{
	std::vector<df::Object *> objs = WM.getAllObjects();
	for (df::Object *obj : objs) {
		if (obj->getType() == "Player") {
			Player* p = dynamic_cast<Player*>(obj);
			if (p->getChargeShot() == this) {
				p->setChargeShot(NULL);
				p->setIsCharging(false);
			}
		}
	}
}
