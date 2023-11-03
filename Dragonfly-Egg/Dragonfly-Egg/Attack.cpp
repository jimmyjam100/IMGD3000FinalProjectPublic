#include "Attack.h"
#include "Player.h"
#include "WorldManager.h"

Attack::Attack() {
	setDamage(0);
	setKnockback(df::Vector());
	setHitstun(0);
	setPlayerOwner(0);
	m_player_owner = NULL;
}

int Attack::eventHandler(const df::Event* p_e)
{
	if (p_e->getType() == COLLISION_EVENT) {
		const df::EventCollision* p_collision_event = dynamic_cast <df::EventCollision const*> (p_e);
		hit(p_collision_event);
		return 1;
	}
	return 0;
}

void Attack::hit(const df::EventCollision* p_collision_event)
{
	// if hits player, destroy projectile, do damage and knockback to player
	if (((p_collision_event->getObject1()->getType()) == "Player") ||
		((p_collision_event->getObject2()->getType()) == "Player")) {
		Player* p_player;
		Attack* p_attack;
		if ((p_collision_event->getObject1()->getType()) == "Player") {
			p_player = dynamic_cast <Player*> (p_collision_event->getObject1());
			p_attack = dynamic_cast <Attack*> (p_collision_event->getObject2());
		}
		else {
			p_player = dynamic_cast <Player*> (p_collision_event->getObject2());
			p_attack = dynamic_cast <Attack*> (p_collision_event->getObject1());
		}

		// if player isn't the same one that shot the projectile, handle a hit
		if (p_attack->getPlayerOwner() != p_player->getPlayerNum()) {
			p_player->hanndleKnockback(p_attack);
		}
	}
}

df::Vector Attack::getKnockback() const {
	return m_knockback;
}

void Attack::setKnockback(df::Vector new_knockback) {
	m_knockback = new_knockback;
}

int Attack::getHitstun() const {
	return m_hitstun;
}

void Attack::setHitstun(int new_hitstun) {
	m_hitstun = new_hitstun;
}

int Attack::getDamage() const {
	return m_damage;
}

void Attack::setDamage(int new_damage) {
	m_damage = new_damage;
}

int Attack::getPlayerOwner() const {
	return m_player_owner;
}

void Attack::setPlayerOwner(int new_player_owner) {
	m_player_owner = new_player_owner;
}

