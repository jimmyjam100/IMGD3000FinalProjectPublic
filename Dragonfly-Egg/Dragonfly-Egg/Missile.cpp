#include "Missile.h"
#include "ResourceManager.h"

// Missle projectile properties:
// Deals 12%, moderate knockback, moderate hitstun
// moves horizontally depending on player orientation

Missile::Missile(df::Vector direction, df::Vector position, int player_owner) {
	setDamage(12);
	setKnockback(df::Vector(3,-2));
	setHitstun(35);
	if (direction.getX() > 0) {
		setSprite("rightmissile");
	}
	else {
		setSprite("leftmissile");
	}
	setDirection(direction);
	setSpeed(.7);
	setPosition(position);
	setType("Missile");
	setSolidness(df::SOFT);
	setPlayerOwner(player_owner);
	RM.getSound("missile")->play();
}
