#include "Projectile.h"
#include "Attack.h"
#include "EventCollision.h"
#include "EventOut.h"
#include "WorldManager.h"
#include "Player.h"
#include "ResourceManager.h"

Projectile::Projectile() {
	setSolidness(df::SOFT);
	setPlayerOwner(0);
}

int Projectile::eventHandler(const df::Event* p_e) {
	
	if (p_e->getType() == COLLISION_EVENT) {
		const df::EventCollision* p_collision_event = dynamic_cast <df::EventCollision const*> (p_e);
		hit(p_collision_event);
		return 1;
	}

	if (p_e->getType() == OUT_EVENT) {
		WM.markForDelete(this);
		return 1;
	}
	return 0;
}

void Projectile::hit(const df::EventCollision* p_collision_event) {
	// if hits player, destroy projectile, do damage and knockback to player
	if (((p_collision_event->getObject1()->getType()) == "Player")) {
		Player* p_player;
		Projectile* p_projectile;
		if ((p_collision_event->getObject1()->getType()) == "Player") {
			p_player = dynamic_cast <Player*> (p_collision_event->getObject1());
			p_projectile = dynamic_cast <Projectile*> (p_collision_event->getObject2());
		}
		else {
			p_player = dynamic_cast <Player*> (p_collision_event->getObject2());
			p_projectile = dynamic_cast <Projectile*> (p_collision_event->getObject1());
		}

		if (p_projectile->getType() == "ChargeShot") {
			ChargeShot* chargeShot = dynamic_cast <ChargeShot*> (p_projectile);
			if (!chargeShot->canHit()) {
				return;
			}
		}

		if (p_projectile->getType() == "Reflector" && p_projectile->getPlayerOwner() != p_player->getPlayerNum()) {
			Reflector* reflector = dynamic_cast <Reflector*> (p_projectile);
			if (reflector->isEarly() && !reflector->hasHit()) {
				p_player->hanndleKnockback(reflector);
				reflector->setHasHit(true);
				RM.getSound("reflect")->play();
				std::vector<Object*> allObjs = WM.getAllObjects();
				std::vector<Object*>::iterator it = allObjs.begin();
				while (it != allObjs.end()) {
					if ((*it)->getType() == "Player") {
						Player* player = dynamic_cast<Player*> (*it);
						if (player->getPlayerNum() == reflector->getPlayerOwner()) {
							player->setCooldown(5);
							break;
						}
					}
					it++;
				}
			}
			return;
		}

		// if player isn't the same one that shot the projectile, handle a hit
		if (p_projectile->getPlayerOwner() != p_player->getPlayerNum()) {
			if (!(p_player->hasReflecter())) {
				p_player->hanndleKnockback(p_projectile);
				WM.markForDelete(p_projectile);
			}
		}
	}

	
}