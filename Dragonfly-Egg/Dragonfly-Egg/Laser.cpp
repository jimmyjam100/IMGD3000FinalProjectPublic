#include "Laser.h"
#include "ResourceManager.h"

// Laser projectile properties:
// Deals 3%, no knockback, no hitstun
// moves horizontally depending on player orientation

Laser::Laser(df::Vector direction, df::Vector position, int player_owner) {
	setDamage(3);
	setKnockback(df::Vector());
	setHitstun(0);
	setSprite("laser");
	setDirection(direction);
	setSpeed(1.5);
	setPosition(position);
	setType("Laser");
	setSolidness(df::SOFT);
	setPlayerOwner(player_owner);
	RM.getSound("fireLaser")->play();
	setBox(df::Box(df::Vector(3, 0), 3, 1));
}