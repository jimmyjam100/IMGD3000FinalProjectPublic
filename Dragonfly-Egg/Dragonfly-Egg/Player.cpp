#include "Player.h"
#include "DisplayManager.h"
#include "Laser.h"
#include "Missile.h"
#include "ChargeShot.h"
#include "WorldManager.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include "GameWin.h"

const float playerSpeed = 0.6;
const float playerJump = -0.75;
const float gravity = 0.045;

bool boxIntersectsBox(df::Box b1, df::Box b2) {
	if (b1.getCorner().getX() + b1.getHorizontal() > b2.getCorner().getX() &&
		b1.getCorner().getX() < b2.getCorner().getX() + b2.getHorizontal() &&
		b1.getCorner().getY() + b1.getVertical() > b2.getCorner().getY() &&
		b1.getCorner().getY() < b2.getCorner().getY() + b2.getVertical()) {
		return true;
	}
	return false;
}

df::Box getWorldBox(const df::Object* p_o) {
	df::Box temp_box = p_o->getBox();
	df::Vector corner = temp_box.getCorner();
	corner.setX(corner.getX() + p_o->getPosition().getX());
	corner.setY(corner.getY() + p_o->getPosition().getY());
	temp_box.setCorner(corner);
	return temp_box;
}




Player::Player(bool right, df::Object* logo)
{
	setType("Player");
	setSolidness(df::SOFT);
	m_cooldown = 0;
	m_hitstun = 0;
	m_percent = 0;
	m_player_speed = 0.35;
	m_charge_shot = NULL;
	m_taunt_cooldown = 0;
	is_charging = false;
	vo = new df::ViewObject();
	vo->setViewString("Percent:");
	stock_vo = new df::ViewObject();
	stock_vo->setViewString("Stocks:");
	stocks = 3;
	stock_vo->setValue(stocks);
	if (right) {
		setSprite("leftplayer2");
		current_sprite = "leftplayer2";
		m_right = true;
		m_playernum = 2;
		setPosition(df::Vector(DM.getHorizontal() - 16, DM.getVertical() - getBox().getVertical()));
		vo->setLocation(df::TOP_RIGHT);
		vo->setColor(df::BLUE);
		stock_vo->setLocation(df::TOP_RIGHT);
		stock_vo->setPosition(stock_vo->getPosition() - df::Vector(0, 1));
		stock_vo->setColor(df::CYAN);
	}
	else {
		setSprite("rightplayer1");
		current_sprite = "rightplayer1";
		m_right = false;
		m_playernum = 1;
		setPosition(df::Vector(16, DM.getVertical() - getBox().getVertical()));
		vo->setLocation(df::TOP_LEFT);
		vo->setColor(df::BLUE);
		stock_vo->setLocation(df::TOP_LEFT);
		stock_vo->setPosition(stock_vo->getPosition() - df::Vector(0, 1));
		stock_vo->setColor(df::YELLOW);
	}
	p_other_player = NULL;
	usedDouble = false;
	holdJump = false;
	jumping = false;
	alreadyOut = false;
	setBox(df::Box(df::Vector(0, -1), 9, 4));
	m_logo = logo;
}

Player::~Player() {
	WM.markForDelete(vo);
	WM.markForDelete(stock_vo);
	if (m_charge_shot != NULL) {
		WM.markForDelete(m_charge_shot);
	}
	if (m_reflector != NULL) {
		WM.markForDelete(m_reflector);
	}
}

int Player::eventHandler(const df::Event* p_e)
{
	if (p_e->getType() == "df::gamepad") {
		hanndleGamepad((df::EventGamepad*)p_e);
		return 1;
	}
	else if (p_e->getType() == "df::step") {
		hanndleStep();
		return 1;
	}
	else if (p_e->getType() == "df::out") {		
		--stocks;
		setPosition(df::Vector(DM.getHorizontal() / 2, -10));
		if (stocks == 0) {
			endGame();
		}
		m_hitstun = 0;
		m_cooldown = 0;
		m_percent = 0;
		m_shoot_cooldown = 0;
		vo->setValue(0);
		vo->setColor(df::BLUE);
		stock_vo->setValue(stocks);
		setVelocity(df::Vector());
		alreadyOut = true;
		RM.getSound("deathblast")->play();
	}
	return 0;
}

void Player::hanndleGamepad(df::EventGamepad* e)
{
	if (m_hitstun <= 0 && stocks > 0) {
		float saveX = getPosition().getX();
		df::Vector v = getPosition();
		if (m_playernum == 1) {
			m_taunt_cooldown = 0;
			switch (e->getButton()) {
			case df::Gamepad::Left1:
				v.setX(v.getX() - playerSpeed);
				break;
			case df::Gamepad::Right1:
				v.setX(v.getX() + playerSpeed);
				break;
			case df::Gamepad::Up1:
				jumping = true;
				break;
			case df::Gamepad::A1:
				shoot(3);
				break;
			case df::Gamepad::B1:
				shoot(2);
				break;
			case df::Gamepad::X1:
				shoot(0);
				break;
			case df::Gamepad::Y1:
				shoot(1);
				break;
			case df::Gamepad::Start1:
				break;
			case df::Gamepad::Select1:
				if (!jumping) {
					m_taunt_cooldown = 40;
					RM.getSound("howl")->play();
					m_hitstun = 25;
				}
				break;
			}
		}
		if (m_playernum == 2) {
			m_taunt_cooldown = 0;
			switch (e->getButton()) {
			case df::Gamepad::Left2:
				v.setX(v.getX() - playerSpeed);
				break;
			case df::Gamepad::Right2:
				v.setX(v.getX() + playerSpeed);
				break;

			case df::Gamepad::Up2:
				jumping = true;
				break;
			case df::Gamepad::A2:
				shoot(3);
				break;
			case df::Gamepad::B2:
				shoot(2);
				break;
			case df::Gamepad::X2:
				shoot(0);
				break;
			case df::Gamepad::Y2:
				shoot(1);
				break;
			case df::Gamepad::Start2:
				break;
			case df::Gamepad::Select2:
				if (!jumping) {
					m_taunt_cooldown = 40;
					RM.getSound("howl")->play();
					m_hitstun = 25;
				}
				break;
			}
		}
		setPosition(v);
	}
	if (!boxIntersectsBox(getWorldBox(this), WM.getBoundary())) {
		if (!alreadyOut) {
			--stocks;
			setPosition(df::Vector(DM.getHorizontal() / 2, -5));
			if (stocks == 0) {
				endGame();
			}
			m_hitstun = 0;
			m_cooldown = 0;
			m_percent = 0;
			vo->setValue(0);
			vo->setColor(df::BLUE);
			stock_vo->setValue(stocks);
			setVelocity(df::Vector());
		}
		alreadyOut = true;
	}
	else {
		alreadyOut = false;
	}
}

void Player::hanndleStep()
{
	if (jumping) {
		df::Vector v = getPosition();
		if (!holdJump) {
			bool onGround = v.getY() == DM.getVertical() - getBox().getVertical();
			if (onGround || !usedDouble ) {
				setVelocity(df::Vector(0, playerJump));
				if (!onGround) {
					usedDouble = true;
				}
			}
		}
		holdJump = true;
	}
	else {
		holdJump = false;
	}
	jumping = false;
	
	if (m_reflector != NULL) {
		if (m_reflector->getActiveTime() == 5 && !m_reflector->hasHit())
			RM.getSound("reflectmiss")->play();
	}

	if (getPosition().getY() >= DM.getVertical() - getBox().getVertical() && getDirection().getY() > 0) {
		setVelocity(df::Vector(0, 0));
		usedDouble = false;
		setPosition(df::Vector(getPosition().getX(), DM.getVertical() - getBox().getVertical()));
	}
	else if (getPosition().getY() < DM.getVertical() - getBox().getVertical()) {
		df::Vector cur = getDirection();
		cur.scale(getSpeed());
		setVelocity(df::Vector(cur.getX(), cur.getY() + gravity));
	}
	if (m_charge_shot != NULL) {
		if (is_charging) {
			int old_charge = m_charge_shot->getCharge();
			m_charge_shot->setCharge(old_charge + 1);
			if (m_charge_shot->isFullyCharged()) {
				is_charging = false;
				m_charge_shot->setCanHit(false);
			}
		}
		df::Vector p = getPosition();
		if (m_right) {
			p += df::Vector(-5, 0);
		}
		else {
			p += df::Vector(5, 0);
		}
		m_charge_shot->setPosition(p);
		if (m_charge_shot->isFullyCharged()) {
			m_charge_shot->setSprite("ncs");
			m_charge_shot->setCanHit(false);
		}
	}
	if (old_reflector != NULL) {
		WM.markForDelete(old_reflector);
		old_reflector = NULL;
	}
	if (m_reflector != NULL) {
		df::Vector p = getPosition();
		m_reflector->setPosition(p);
		m_reflector->setActiveTime(m_reflector->getActiveTime() + 1);
		if (m_reflector->getActiveTime() > 12) {
			old_reflector = m_reflector;
			m_reflector = NULL;
		}
	}
	
	if (m_taunt_cooldown > 0) {
		--m_taunt_cooldown;
	}
	if (stocks > 0) {
		if (m_hitstun > 0) {
			--m_hitstun;
		}
		if (m_cooldown > 0) {
			--m_cooldown;
		}
	}

	if (m_shoot_cooldown > 0) {
		--m_shoot_cooldown;
	}
	if (p_other_player == NULL) {
		std::vector<df::Object *> all =  WM.getAllObjects();
		for (Object* o : all) {
			if (o->getType() == "Player" && o->getId() != getId()) {
				p_other_player = (Player *)o;
			}
		}
	}
	else {
			if (p_other_player->getPosition().getX() > getPosition().getX()) {
				//player facing right
				m_right = false;
				if (m_taunt_cooldown > 0) {
					if (m_playernum == 1 && current_sprite != "righttaunt1"){
						setSprite("righttaunt1");
						current_sprite = "righttaunt1";
					}
					else if (m_playernum == 2 && current_sprite != "rightaunt2") {
						setSprite("righttaunt2");
						current_sprite = "righttaunt2";
					}
				}
				else if (m_hitstun > 0) {
					if (current_sprite != "righthitstun") {
						setSprite("righthitstun");
						current_sprite = "righthitstun";
					}
				}
				else if (m_shoot_cooldown > 0) {
					if (m_playernum == 1 && current_sprite != "rightshoot1") {
						setSprite("rightshoot1");
						current_sprite = "rightshoot1";
					}
					else if (m_playernum == 2 && current_sprite != "rightshoot2") {
						setSprite("rightshoot2");
						current_sprite = "rightshoot2";
					}
				}
				else if (m_playernum == 1 && current_sprite != "rightplayer1") {
					setSprite("rightplayer1");
					current_sprite = "rightplayer1";
				}
				else if (m_playernum == 2 && current_sprite != "rightplayer2") {
					setSprite("rightplayer2");
					current_sprite = "rightplayer2";
				}
				if (m_charge_shot != NULL) {
					m_charge_shot->setDirection(df::Vector(1, 0));
				}
			}
			else {
				m_right = true;
				if (m_taunt_cooldown > 0) {
					if (m_playernum == 1 && current_sprite != "lefttaunt1") {
						setSprite("lefttaunt1");
						current_sprite = "lefttaunt1";
					}
					else if (m_playernum == 2 && current_sprite != "lefttaunt2") {
						setSprite("lefttaunt2");
						current_sprite = "lefttaunt2";
					}
				}
				else if (m_hitstun > 0) {
					if (current_sprite != "lefthitstun") {
						setSprite("lefthitstun");
						current_sprite = "lefthitstun";
					}
				}
				else if (m_shoot_cooldown > 0) {
					if (m_playernum == 1 && current_sprite != "leftshoot1") {
						setSprite("leftshoot1");
						current_sprite = "leftshoot1";
					}
					else if (m_playernum == 2 && current_sprite != "leftshoot2") {
						setSprite("leftshoot2");
						current_sprite = "leftshoot2";
					}
				}
				else if (m_playernum == 1 && current_sprite != "leftplayer1") {
					setSprite("leftplayer1");
					current_sprite = "leftplayer1";
				}
				else if (m_playernum == 2 && current_sprite != "leftplayer2") {
					setSprite("leftplayer2");
					current_sprite = "leftplayer2";
				}
				if (m_charge_shot != NULL) {
					m_charge_shot->setDirection(df::Vector(-1, 0));
				}
			}
	}
	//setSprite("floor");
}

void Player::hanndleKnockback(Attack* p)
{
	m_percent += p->getDamage();
	if (m_hitstun < p->getHitstun())
		m_hitstun = p->getHitstun();

	df::Vector v = p->getKnockback();
	if (p->getType() == "Reflector") {
		v.scale(80);
		v.scale(0.002);
	}
	else {
		v.scale(m_percent);
		v.scale(0.002);
	}
	df::Vector v2 = p->getXVelocity();
	if (v2.getMagnitude() == 0) {
		if (m_right) {
			v2.setX(1);
		}
		else {
			v2.setX(-1);
		}
	}
	v2.normalize();
	v.setX(v.getX() * v2.getX());
	if (m_hitstun > 0) {
		setVelocity(v);
		RM.getSound("hit")->play();
		m_taunt_cooldown = 0;
		m_cooldown = 0;
	}
	vo->setValue(m_percent);
	if (m_percent > 100) {
		vo->setColor(df::RED);
	}
	else if (m_percent > 50) {
		vo->setColor(df::MAGENTA);
	}
}

void Player::shoot(int weapon) {
	if (m_cooldown == 0) {
		df::Vector p; // position
		df::Vector d; // direction
		switch (weapon) {
		case 0:
			if (is_charging) {
				// shoot charged charge shot
				if (m_charge_shot->isFullyCharged()) {
					m_charge_shot->shootFull();
				}
				m_charge_shot->setPlayerOwner(m_playernum);
				m_charge_shot->setSpeed(.75);
				m_charge_shot->setCanHit(true);
				is_charging = false;
				if (m_charge_shot->getSize() == "small") {
					m_cooldown = 20;
				}
				else if (m_charge_shot->getSize() == "medium") {
					m_cooldown = 30;
				}
				else
					m_cooldown = 60;
				m_charge_shot = NULL;
				m_shoot_cooldown = 15;
				RM.getSound("chargeshot")->play();
				break;
			}
			p = getPosition();
			d = df::Vector();
			if (m_right) {
				p += df::Vector(-5, -1);
				d = df::Vector(-1, 0);
			}
			else {
				p += df::Vector(5, -1);
				d = df::Vector(1, 0);
			}

			new Laser(d, p, m_playernum);
			m_cooldown = 10;
			m_shoot_cooldown = 5;
			break;
		case 1:
			if (is_charging && m_charge_shot != NULL) {
				if (m_charge_shot->isFullyCharged()) {
					m_charge_shot->shootFull();
				}
				// shoot charged charge shot
				m_charge_shot->setPlayerOwner(m_playernum);
				m_charge_shot->setSpeed(.75);
				m_charge_shot->setCanHit(true);
				is_charging = false;
				if (m_charge_shot->getSize() == "small") {
					m_cooldown = 25;
				}
				else if (m_charge_shot->getSize() == "medium") {
					m_cooldown = 35;
				}
				else
					m_cooldown = 60;
				m_charge_shot = NULL;
				m_shoot_cooldown = 15;
				RM.getSound("chargeshot")->play();
				break;
			}
			p = getPosition();
			d = df::Vector();
			if (m_right) {
				p += df::Vector(-6, 0);
			}
			else {
				p += df::Vector(8, 0);
			}

			if (p_other_player == NULL) {
				d = df::Vector();
			}
			else {
				d = p_other_player->getPosition() - p;
				d.normalize();
			}
			new Missile(d, p, m_playernum);
			m_cooldown = 40;
			m_shoot_cooldown = 10;
			break;
		case 2:
			if (m_charge_shot == NULL) {
				
				p = getPosition();
				d = df::Vector();
				if (m_right) {
					p += df::Vector(-5, 0);
					d = df::Vector(-1, 0);
				}
				else {
					p += df::Vector(5, 0);
					d = df::Vector(1, 0);
				}

				m_charge_shot = new ChargeShot(d, p, m_playernum);
				is_charging = true;
			} else if (m_charge_shot->isFullyCharged()) {
				// shoot charged charge shot
				m_charge_shot->setPlayerOwner(m_playernum);
				m_charge_shot->shootFull();
				is_charging = false;
				m_charge_shot = NULL;
				m_cooldown = 50;
				m_shoot_cooldown = 15;
				RM.getSound("chargeshot")->play();
			}
			else if (!is_charging) {
				is_charging = true;
				m_charge_shot->updateSprite();
			}
			break;
		case 3:
			if (is_charging && m_charge_shot != NULL) {
				is_charging = false;
				m_charge_shot->setSprite("ncs"); // hide the charge shot
				m_charge_shot->setCanHit(false);
			}
			else if (m_reflector == NULL) {
				m_reflector = new Reflector(getPosition(), m_playernum);
				m_cooldown = 70;
			}
		}
		
	}
}

int Player::getPlayerNum() const {
	return m_playernum;
}

bool Player::hasReflecter() const
{
	return m_reflector != NULL;
}

void Player::setCooldown(int cooldown)
{
	m_cooldown = cooldown;
}

ChargeShot* Player::getChargeShot() const
{
	return m_charge_shot;
}

void Player::setChargeShot(ChargeShot* c)
{
	m_charge_shot = c;
}

Reflector* Player::getReflector() const
{
	return m_reflector;
}

void Player::setReflector(Reflector* r)
{
	m_reflector = r;
}

void Player::setIsCharging(bool c)
{
	is_charging = c;
}

void Player::endGame()
{
	bool gameover = false;
	std::vector<Object*> allObjs = WM.getAllObjects();
	std::vector<Object*>::iterator it = allObjs.begin();
	while (it != allObjs.end()) {
		if ((*it)->getType() == "gamewin") {
			gameover = true;
			break;
		}
		++it;
	}
	if (m_playernum == 1 && !gameover) {
		new GameWin(2);
	}
	else if (!gameover) {
		new GameWin(1);
	}
	setPosition(df::Vector(-30, 0));
	m_hitstun = 30;
	m_cooldown = 30;
}
