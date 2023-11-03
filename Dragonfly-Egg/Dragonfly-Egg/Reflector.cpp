#include "Reflector.h"
#include "Player.h"
#include "ResourceManager.h"
#include "WorldManager.h"

Reflector::Reflector(df::Vector position, int player_owner)
{
	setDamage(5);
	setKnockback(df::Vector(1, -5));
	setHitstun(15);
	setSprite("reflector");
	setPosition(position);
	setType("Reflector");
	setSolidness(df::SOFT);
	setPlayerOwner(player_owner);
	active_time = 0;
	has_hit = false;
}

int Reflector::getActiveTime() const
{
	return active_time;
}

void Reflector::setActiveTime(int new_active_time)
{
	active_time = new_active_time;
}

bool Reflector::hasHit() const
{
	return has_hit;
}

void Reflector::setHasHit(bool new_bool)
{
	has_hit = new_bool;
}

bool Reflector::isEarly() const
{
	if (active_time <= 4) {
		return true;
	}
	return false;
}

int Reflector::eventHandler(const df::Event* p_e)
{
	if (p_e->getType() == "df::collision") {
		const df::EventCollision* p_2 = dynamic_cast<const df::EventCollision*>(p_e);
		if (p_2->getObject1()->getType() == "Laser" ||
			p_2->getObject1()->getType() == "Missile" ||
			p_2->getObject1()->getType() == "ChargeShot") {
			Projectile* proj = dynamic_cast<Projectile*>(p_2->getObject1());
			if (proj->getPlayerOwner() != getPlayerOwner()) {
				if (isEarly()) {
					proj->setPlayerOwner(getPlayerOwner());
					df::Vector v = df::Vector(-proj->getXVelocity().getX(), proj->getYVelocity().getY());
					v.scale(1.2);
					proj->setVelocity(v);
					proj->setDamage(proj->getDamage() * 1.2);
					if (proj->getType() == "Missile" && proj->getXVelocity().getX() > 0) {
						proj->setSprite("rightmissile");
					}
					else if (proj->getType() == "Missile") {
						proj->setSprite("leftmissile");
					}
					RM.getSound("reflect")->play();
					std::vector<Object*> allObjs = WM.getAllObjects();
					std::vector<Object*>::iterator it = allObjs.begin();
					while (it != allObjs.end()) {
						if ((*it)->getType() == "Player") {
							Player* player = dynamic_cast<Player*> (*it);
							if (player->getPlayerNum() == proj->getPlayerOwner()) {
								player->setCooldown(0);
								break;
							}
						}
						it++;
					}
				} else {
					WM.markForDelete(proj);
					RM.getSound("shield")->play();
				}
			}
			return 1;
		} 
	}
	Projectile::eventHandler(p_e);
	return 0;
}

Reflector::~Reflector()
{
	std::vector<df::Object*> objs = WM.getAllObjects();
	for (df::Object* obj : objs) {
		if (obj->getType() == "Player") {
			Player* p = dynamic_cast<Player*>(obj);
			if (p->getReflector() == this) {
				p->setReflector(NULL);
			}
		}
	}
}
